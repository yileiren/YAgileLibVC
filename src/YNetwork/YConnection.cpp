#include "../../include/YNetwork/YConnection.h"

using namespace YLR;

YConnection::YConnection()
{
}

bool YConnection::setRcvTimeOut(SOCKET s,const int &t)
{
	int z = setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char *)&t,sizeof(int));

	if(z)
		return false;  //失败
	else
		return true;   //成功
}

int YConnection::getRcvTimeOut(SOCKET s)
{
	int rcvbuf = 0;
	int optlen = sizeof(int);
	int z = getsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char *)&rcvbuf,&optlen);

	if(z)
		return -1;
	else
		return rcvbuf;
}

bool YConnection::setSndTimeOut(SOCKET s,const int &t)
{
	int z = setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char *)&t,sizeof(int));

	if(z)
		return false;  //失败
	else
		return true;   //成功
}

int YConnection::getSndTimeOut(SOCKET s)
{
	int rcvbuf = 0;
	int optlen = sizeof(int);
	int z = getsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char *)&rcvbuf,&optlen);

	if(z)
		return -1;
	else
		return rcvbuf;
}

bool YConnection::sendData(SOCKET s,const YByteType &data,const int &packageCount,const int &sndTimeOut,const int &rcvTimeOut)
{
	return false;
}