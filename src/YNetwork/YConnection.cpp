#include "../../include/YNetwork/YConnection.h"

using namespace YLR;
using namespace YNetWork;

YConnection::YConnection()
{
}

inline bool YConnection::setRcvTimeOut(SOCKET s,const int &t)
{
	int z = setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char *)&t,sizeof(int));

	if(z)
		return false;  //失败
	else
		return true;   //成功
}

inline int YConnection::getRcvTimeOut(SOCKET s)
{
	int rcvbuf = 0;
	int optlen = sizeof(int);
	int z = getsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char *)&rcvbuf,&optlen);

	if(z)
		return -1;
	else
		return rcvbuf;
}

inline bool YConnection::setSndTimeOut(SOCKET s,const int &t)
{
	int z = setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char *)&t,sizeof(int));

	if(z)
		return false;  //失败
	else
		return true;   //成功
}

inline int YConnection::getSndTimeOut(SOCKET s)
{
	int rcvbuf = 0;
	int optlen = sizeof(int);
	int z = getsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char *)&rcvbuf,&optlen);

	if(z)
		return -1;
	else
		return rcvbuf;
}

bool YConnection::sendData(SOCKET s,const YDataType::YByteType &data,const int &packageLength,const int &sndTimeOut,const int &rcvTimeOut)
{
	bool retValue = true;; //返回值
	//初始化套接字
	YConnection::setSndTimeOut(s,sndTimeOut);
	YConnection::setRcvTimeOut(s,rcvTimeOut);

	//请求发送数据
	YBYTE reqData[14];
	memset(reqData,0,14);
	reqData[0] = YConnection::SendData;
	int i = 1;
	memcpy(reqData + 1,&i,4);
	memcpy(reqData + 5,&i,4);
	i = 0;
	memcpy(reqData + 9,&i,4);
	reqData[13] = YConnection::EndFlag;

	int r = send(s,(const char *)reqData,14,0);
	if(SOCKET_ERROR != r)
	{
		//发送请求后接收对方回复
		r = recv(s,(char *)reqData,14,0);
		if(SOCKET_ERROR != r)
		{
			if(YConnection::Yes == reqData[0])
			{
				//发送数据
				YBYTE * buf = new YBYTE[packageLength + 14];
				buf[0] = YConnection::DataPackage;

				//计算数据包总数
				int packageCount = data.getSize() / packageLength;
				if(data.getSize() % packageLength > 0)
				{
					packageCount++;
				}
				memcpy(buf + 1,&packageCount,4);

				buf[packageLength + 13] = YConnection::EndFlag;//

				int sendLength = 0; //发送数据计数
				while(data.getSize() - sendLength > 0)
				{
					//初始化包中的数据部分
					memset(buf + 13,0,packageLength);

					//当前数据包序号
					int packageOrder = sendLength / packageLength + 1;
					memcpy(buf + 5,&packageOrder,4);

					int l = 0;
					if(data.getSize() - sendLength >= (unsigned int)packageLength)
					{
						l = packageLength;
						data.getData(buf + 13,l,sendLength);
						sendLength += l;
					}
					else
					{
						l = data.getSize() - sendLength;
						data.getData(buf + 13,l,sendLength);
						sendLength += l;
					}
					//数据包中数据长度
					memcpy(buf + 9,&l,4);

					r = send(s,(const char *)buf,l + 14,0);

					if(SOCKET_ERROR != r)
					{
						r = recv(s,(char *)reqData,14,0);
						if(SOCKET_ERROR != r)
						{
							if(YConnection::Go != reqData[0])
							{
								//对方不允许继续发送数据
								retValue = false;
								break;
							}
						}
						else
						{
							//发送数据包后接收对方回复失败
							retValue = false;
							break;
						}
					}
					else
					{
						//数据包发送失败
						retValue = false;
						break;
					}
				}

				delete[] buf;
			}
			else
			{
				//对方不允许发送数据
				retValue = false;
			}
		}
		else
		{
			//请求发送数据时接收对方回复
			retValue = false;
		}
	}
	else
	{
		//发送数据请求失败
		retValue = false;
	}

	//请求结束
	//请求发送数据
	YBYTE endReqData[14];
	memset(endReqData,0,14);
	endReqData[0] = YConnection::End;
	i = 1;
	memcpy(endReqData + 1,&i,4);
	memcpy(endReqData + 5,&i,4);
	i = 0;
	memcpy(endReqData + 9,&i,4);
	endReqData[13] = YConnection::EndFlag;

	send(s,(const char *)endReqData,14,0);

	return retValue;
}

bool YConnection::recaiveData(SOCKET s,YDataType::YByteType &data,const int &bufLength,const int &sndTimeOut,const int &rcvTimeOut)
{
	bool retValue = false;
	//初始化套接字
	YConnection::setSndTimeOut(s,sndTimeOut);
	YConnection::setRcvTimeOut(s,rcvTimeOut);

	YBYTE * rcvBuf = new YBYTE[bufLength]; //接收数据缓冲区。
	memset(rcvBuf,0,bufLength);

	//接收请求
	int r = recv(s,(char *)rcvBuf,bufLength,0);
	if(SOCKET_ERROR != r)
	{
		if(YConnection::SendData == rcvBuf[0])
		{
			YBYTE resData[14]; //响应数据
			resData[0] = YConnection::Yes;
			int i = 1;
			memcpy(resData + 1,&i,4);
			memcpy(resData + 5,&i,4);
			i = 0;
			memcpy(resData + 9,&i,4);
			resData[13] = YConnection::EndFlag;

			//允许传输
			r = send(s,(const char *)resData,14,0);
			if(SOCKET_ERROR != r)
			{
				//开始接收数据
				data.setSize(0);
				while(true)
				{
					memset(rcvBuf,0,bufLength); //初始化缓冲区
					r = recv(s,(char *)rcvBuf,bufLength,0);
					if(SOCKET_ERROR != r)
					{
						if(YConnection::DataPackage == rcvBuf[0])
						{
							int packageLength = 0; //数据包中数据长度
							memcpy(&packageLength,rcvBuf + 9,4);
							if(packageLength > 0)
							{
								data.setSize(data.getSize() + packageLength);
								data.setData(rcvBuf + 13,packageLength,data.getSize() - packageLength);
							}

							//继续接收数据
							resData[0] = YConnection::Go;
							r = send(s,(const char *)resData,14,0);
							if(SOCKET_ERROR == r)
							{
								//继续发送数据响应失败
								break;
							}
						}
						else if(YConnection::End == rcvBuf[0])
						{
							//接收数据完成。
							retValue = true;
							break;
						}
						else
						{
							//接收到得数据不是数据包，发送出错响应并停止接收。
							resData[0] = YConnection::Error;
							send(s,(const char *)resData,14,0);
							break;
						}
					}
					else
					{
						//接收数据失败
						break;
					}
				}
			}//发送允许传输响应失败
		}//判断请求位为发送数据请求
	}//接收请求数据

	delete[] rcvBuf;
	return retValue;
}