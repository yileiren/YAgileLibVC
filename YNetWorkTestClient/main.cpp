#include <iostream>
#include <string>

#include "../include/YNetwork/YConnection.h"

/*!
 * \brief
 * 发送数据测试方法。
 */
void sendData()
{
	std::string ip;
	int port;
	std::cout<<"请输入服务器IP：";
	std::cin>>ip;
	if(ip == "")
	{
		ip = "127.0.0.1";
	}

	std::cout<<"请输入服务器监听端口：";
	std::cin>>port;

	//创建套接字
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested,&wsaData);
	if ( err == 0 ) 
	{
		//连接服务器
		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr=inet_addr(ip.c_str());
		addrSrv.sin_family=AF_INET;
		addrSrv.sin_port=htons(port);

		std::string sendText;
		std::cout<<"请输入您要发送的文字：";
		std::cin>>sendText;

		//创建套接字
		SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);
		if(INVALID_SOCKET != sockClient)
		{
			err = connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

			if(SOCKET_ERROR != err)
			{
				std::cout<<"发送服务器ip为："<<ip<<"，服务器端口为："<<port<<"。"<<std::endl;;

				YLR::YDataType::YByteType data((unsigned int)sendText.size() + 1,(const YBYTE *)sendText.c_str());

				YLR::YNetWork::YConnection con;
				bool r = con.sendData(sockClient,data,20,10000,10000);
				if(r)
				{
					std::cout<<"发送数据成功！"<<std::endl;
				}
				else
				{
					std::cout<<"发送数据失败！"<<std::endl;
				}
			}
			else
			{
				std::cout<<"连接服务器失败！"<<std::endl;
			}
		}
		else
		{
			std::cout<<"创建套接字失败！"<<std::endl;
		}

		closesocket(sockClient);
		WSACleanup();
	}
}

int main()
{
	while(true)
	{
		int inputNum = 0; //输入的选择序号。
		std::cout<<"YNetwork测试程序客户端已启动，请选择您要进行的操作："<<std::endl;
		std::cout<<"1：数据发送。"<<std::endl;
		std::cout<<"0：退出程序。"<<std::endl;
		std::cout<<"请输入您的选择：";
		std::cin>>inputNum;

		if(0 == inputNum)
		{
			std::cout<<"程序已经退出！"<<std::endl;
			break;
		}
		else if(1 == inputNum)
		{
			sendData();
		}
		else
		{
			std::cout<<"您输入的序号不正确，请重新输入！"<<std::endl;
		}
	}

	return 0;
}