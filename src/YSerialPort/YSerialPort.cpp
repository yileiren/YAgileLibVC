#include "..\..\include\YSerialPort\YSerialPort.h"

using namespace YLR;

YSerialPort::YSerialPort(void) : 
	serialNum(1),
	baudRate(9600),
	byteSize(8),
	parity(NoParity),
	stopBits(OneStopBit),
	serialPort(NULL)
{

}

YSerialPort::~YSerialPort(void)
{
	this->closeSerialPort();
}

bool YSerialPort::openSerialPort(void)
{
	//生成串口号
	//LPCTSTR com;

#ifdef UNICODE
	WCHAR a[8];
	memset(a,'\0',sizeof(a));
	wsprintf(a,L"COM%d:",this->serialNum);
	//com = a;
#else
	CHAR a[8];
	memset(a,'\0',sizeof(a));
	sprintf(a,L"COM%d:",this->serialNum);
	//com = a;
#endif

	//打开串口
	this->serialPort = CreateFile(a,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if(this->serialPort == NULL)
	{
		return false;
	}

	//设置串口
	DCB  PortDCB;
	PortDCB.DCBlength = sizeof(DCB);
	GetCommState(this->serialPort,&PortDCB);
	PortDCB.BaudRate = this->baudRate;
	PortDCB.ByteSize = this->byteSize;
	PortDCB.Parity = this->parity; 
	PortDCB.StopBits = this->stopBits;  
	if (!SetCommState(this->serialPort, &PortDCB))
	{
		return false;
	}

	//配置超时值
	COMMTIMEOUTS  CommTimeouts;
	GetCommTimeouts(this->serialPort, &CommTimeouts);
	CommTimeouts.ReadIntervalTimeout = 1000;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 50;  
	CommTimeouts.ReadTotalTimeoutConstant = 100;    
	CommTimeouts.WriteTotalTimeoutMultiplier = 50;  
	CommTimeouts.WriteTotalTimeoutConstant = 100;    
	if (!SetCommTimeouts(this->serialPort, &CommTimeouts))
	{
		return false;
	}         

	return true;
}

int YSerialPort::sendData(const unsigned char * data, const int & count)
{
	if(this->serialPort != NULL)
	{
		//清空串口缓冲区
		if(!PurgeComm(this->serialPort,PURGE_TXCLEAR))
		{
			return -3;
		}

		if(!PurgeComm(this->serialPort,PURGE_RXCLEAR))
		{
			return -4;
		}

		unsigned long int numBytes = 0; //发送的字节数
		if(WriteFile (this->serialPort, // 句柄
			data, // 数据缓冲区地址
			count, // 数据数量
			&numBytes, // 返回发送出去的字节数
			NULL // 不支持重叠
			))

		{
			return numBytes;
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -1;
	}
}

int YSerialPort::receiveDate(unsigned char * data, const int & count)
{
	if(this->serialPort != NULL)
	{
		unsigned long int numBytes = 0; //接收的字节数

		SetCommMask(this->serialPort, EV_RXCHAR); //只接收字符

		if(ReadFile(this->serialPort, data, count, &numBytes, 0))
		{
			return numBytes;
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -1;
	}
}

bool YSerialPort::closeSerialPort(void)
{
	if(this->serialPort != NULL)
	{
		if(CloseHandle(this->serialPort))
		{
			this->serialPort = NULL;
		}
		else
		{
			return false;
		}
	}
	return true;
}
