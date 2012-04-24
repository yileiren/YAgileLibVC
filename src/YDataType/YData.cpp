#include "..\..\include\YDataType\YData.h"

#include <memory.h>
#include <sstream>

using namespace YLR;

YData::YData() :
	_type(YData::YNull),
	str(NULL)
{
}

YData::YData(const int &d) :
	str(NULL)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YInt;
}

YData::YData(const double &d) :
	str(NULL)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YDouble;
}

YData::YData(const float &d) :
	str(NULL)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YFloat;
}

YData::YData(const std::string &d) :
	str(NULL)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YString;
}

YData::~YData()
{
	if(this->str != NULL)
	{
		delete this->str;
	}
}

YData::DatyType YData::getDataType() const
{
	return this->_type;
}

void YData::setNull()
{
	this->setSize();
	this->_type = YData::YNull;
}

void YData::setFrom(const int &d)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YInt;
}

void YData::setFrom(const double &d)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YDouble;
}

void YData::setFrom(const float &d)
{
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YFloat;
}

void YData::setFrom(const std::string &d)
{
	//判断C穿长度
	int i = 0;
	const char * p = d.c_str();
	while(*p != NULL)
	{
		i++;
		p++;
	}
	//设置存储空间
	this->setSize(i + 1);

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	i = 0;
	p = d.c_str();
	while(*(p + i) != NULL)
	{
		buf[i] = p[i];
		i++;
	}
	buf[i] = '\0';
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YString;
}

int YData::toInt() const
{
	int data = 0;

	switch(this->_type)
	{
	case YData::YInt:
		{
			YBYTE * buf = new YBYTE[sizeof(int)];
			this->getData(buf,sizeof(int));
			memcpy(&data,buf,sizeof(int));
			delete[] buf;
			break;
		}
	case YData::YDouble:
		{
			YBYTE * buf = new YBYTE[sizeof(double)];
			this->getData(buf,sizeof(double));
			double d = 0;
			memcpy(&d,buf,sizeof(double));
			data = (int)d;
			delete[] buf;
			break;
		}
	case YData::YFloat:
		{
			YBYTE * buf = new YBYTE[sizeof(float)];
			this->getData(buf,sizeof(float));
			float d = 0;
			memcpy(&d,buf,sizeof(float));
			data = (int)d;
			delete[] buf;
			break;
		}
	case YData::YString:
		{
			YBYTE * buf = new YBYTE[this->getSize()];
			this->getData(buf,this->getSize());
			data = atoi((char *)buf);
			delete[] buf;
		}
	}

	return data;
}

double YData::toDouble() const
{
	double data = 0;

	switch(this->_type)
	{
	case YData::YInt:
		{
			YBYTE * buf = new YBYTE[sizeof(int)];
			this->getData(buf,sizeof(int));
			int d = 0;
			memcpy(&d,buf,sizeof(int));
			data = d;
			delete[] buf;
			break;
		}
	case YData::YDouble:
		{
			YBYTE * buf = new YBYTE[sizeof(double)];
			this->getData(buf,sizeof(double));
			memcpy(&data,buf,sizeof(double));
			delete[] buf;
			break;
		}
	case YData::YFloat:
		{
			YBYTE * buf = new YBYTE[sizeof(float)];
			this->getData(buf,sizeof(float));
			float d = 0;
			memcpy(&d,buf,sizeof(float));
			data = d;
			delete[] buf;
			break;
		}
	case YData::YString:
		{
			YBYTE * buf = new YBYTE[this->getSize()];
			this->getData(buf,this->getSize());
			data = atof((char *)buf);
			delete[] buf;
		}
	}

	return data;
}

float YData::toFloat() const
{
	float data = 0;

	switch(this->_type)
	{
	case YData::YInt:
		{
			YBYTE * buf = new YBYTE[sizeof(int)];
			this->getData(buf,sizeof(int));
			int d = 0;
			memcpy(&d,buf,sizeof(int));
			data = (float)d;
			delete[] buf;
			break;
		}
	case YData::YDouble:
		{
			YBYTE * buf = new YBYTE[sizeof(double)];
			this->getData(buf,sizeof(double));
			double d = 0;
			memcpy(&d,buf,sizeof(double));
			data = (float)d;
			delete[] buf;
			break;
		}
	case YData::YFloat:
		{
			YBYTE * buf = new YBYTE[sizeof(float)];
			this->getData(buf,sizeof(float));
			memcpy(&data,buf,sizeof(float));
			delete[] buf;
			break;
		}
	case YData::YString:
		{
			YBYTE * buf = new YBYTE[this->getSize()];
			this->getData(buf,this->getSize());
			data = (float)atof((char *)buf);
			delete[] buf;
		}
	}

	return data;
}

std::string * YData::toString()
{
	if(this->str != NULL)
	{
		delete this->str;
	}
	this->str = new std::string();

	switch(this->_type)
	{
	case YData::YInt:
		{
			YBYTE * buf = new YBYTE[sizeof(int)];
			this->getData(buf,sizeof(int));
			int d = 0;
			memcpy(&d,buf,sizeof(int));
			std::stringstream stream;
			stream << d;
			stream >> *(this->str);
			delete[] buf;
			break;
		}
	case YData::YDouble:
		{
			YBYTE * buf = new YBYTE[sizeof(double)];
			this->getData(buf,sizeof(double));
			double d = 0;
			memcpy(&d,buf,sizeof(double));
			std::stringstream stream;
			stream << d;
			stream >> *(this->str);;
			delete[] buf;
			break;
		}
	case YData::YFloat:
		{
			YBYTE * buf = new YBYTE[sizeof(float)];
			this->getData(buf,sizeof(float));
			float d = 0;
			memcpy(&d,buf,sizeof(float));
			std::stringstream stream;
			stream << d;
			stream >> *(this->str);;
			delete[] buf;
			break;
		}
	case YData::YString:
		{
			YBYTE * buf = new YBYTE[this->getSize()];
			this->getData(buf,this->getSize());

			*(this->str) = std::string((char *)buf);
			delete[] buf;
		}
	}

	return this->str;
}