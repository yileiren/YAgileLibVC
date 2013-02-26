#include <iostream>
#include <string>

#include "../include/YNetwork/YConnection.h"
#include "../include/YDataType/YTextEncode.h"

/*!
 * \brief
 * 接收数据测试方法。
 */
void recvData()
{
	int acceptPort = 0;
	std::cout<<"请输入监听端口号:";
	std::cin>>acceptPort;

	//初始化套接字
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested,&wsaData);
	if ( err != 0 ) 
	{
		WSACleanup();
		std::cout<<"初始化套接字失败！"<<std::endl;
		return;
	}

	//创建套接字
	SOCKET serverSocket = socket(AF_INET,SOCK_STREAM,0);
	if(INVALID_SOCKET == serverSocket)
	{
		WSACleanup();
		std::cout<<"创建套接字失败！"<<std::endl;
		return;
	}

	//绑定端口
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(acceptPort);

	err = bind(serverSocket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	if(SOCKET_ERROR == err)
	{
		WSACleanup();
		std::cout<<"绑定端口失败！"<<std::endl;
		return;
	}

	//设置连接数
	err = listen(serverSocket,200);
	if(SOCKET_ERROR == err)
	{
		WSACleanup();
		std::cout<<"初设置连接数失败！"<<std::endl;
		return;
	}

	SOCKADDR_IN addrClient;//和客户端连接的发送套接字
	int len=sizeof(SOCKADDR);

	//监听启动
	std::cout<<"网络监听已开启！监听端口号："<<acceptPort<<"，等待数据传输..."<<std::endl;
	SOCKET sockConn=accept(serverSocket,(SOCKADDR*)&addrClient,&len);

	YLR::YDataType::YByteType data;
	bool r = YLR::YNetWork::YConnection::recaiveData(sockConn,data,50,1000,1000);
	if(r)
	{
		YBYTE * text = new YBYTE[data.getSize()];
		data.getData(text,data.getSize());

		std::cout<<text<<std::endl;
		delete[] text;
	}
	else
	{
		std::cout<<"接收数据失败！"<<std::endl;
	}

	closesocket(serverSocket);//关闭连接
    WSACleanup();
}

/*!
 * \brief
 * 接收Utf8文本。
 */
void recvUtf8Text()
{
	int acceptPort = 0;
	std::cout<<"请输入监听端口号:";
	std::cin>>acceptPort;

	//初始化套接字
	WORD wVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested,&wsaData);
	if ( err != 0 ) 
	{
		WSACleanup();
		std::cout<<"初始化套接字失败！"<<std::endl;
		return;
	}

	//创建套接字
	SOCKET serverSocket = socket(AF_INET,SOCK_STREAM,0);
	if(INVALID_SOCKET == serverSocket)
	{
		WSACleanup();
		std::cout<<"创建套接字失败！"<<std::endl;
		return;
	}

	//绑定端口
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(acceptPort);

	err = bind(serverSocket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	if(SOCKET_ERROR == err)
	{
		WSACleanup();
		std::cout<<"绑定端口失败！"<<std::endl;
		return;
	}

	//设置连接数
	err = listen(serverSocket,200);
	if(SOCKET_ERROR == err)
	{
		WSACleanup();
		std::cout<<"初设置连接数失败！"<<std::endl;
		return;
	}

	SOCKADDR_IN addrClient;//和客户端连接的发送套接字
	int len=sizeof(SOCKADDR);

	//监听启动
	std::cout<<"网络监听已开启！监听端口号："<<acceptPort<<"，等待数据传输..."<<std::endl;
	SOCKET sockConn=accept(serverSocket,(SOCKADDR*)&addrClient,&len);

	YLR::YDataType::YByteType data;
	bool r = YLR::YNetWork::YConnection::recaiveData(sockConn,data,50,1000,1000);
	if(r)
	{
		YBYTE * text = new YBYTE[data.getSize()];
		data.getData(text,data.getSize());

		std::string utf8Str((char *)text);

		std::string * gbkStr = YLR::YDataType::YTextEncode::utf8ToMultibyte(utf8Str);

		std::cout<<*gbkStr<<std::endl;
		delete[] text;
		YLR::YDataType::YTextEncode::freeText(gbkStr);
	}
	else
	{
		std::cout<<"接收数据失败！"<<std::endl;
	}

	closesocket(serverSocket);//关闭连接
    WSACleanup();
}

int main()
{
	YLR::YDataType::YByteType b;
	while(true)
	{
		int inputNum = 0; //输入的选择序号。
		std::cout<<"YNetwork测试程序服务器端已启动，请选择您要进行的操作："<<std::endl;
		std::cout<<"1：数据接收（GBK格式）。"<<std::endl;
		std::cout<<"2：数据接收（Utf-8格式）。"<<std::endl;
		std::cout<<"3：测试服务器监听方法。"<<std::endl;
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
			recvData();
		}
		else if(2 == inputNum)
		{
			recvUtf8Text();
		}
		else if(3 == inputNum)
		{
			testAccept();
		}
		else
		{
			std::cout<<"您输入的序号不正确，请重新输入！"<<std::endl;
		}
	}

	return 0;
}