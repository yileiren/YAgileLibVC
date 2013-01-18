#include "..\..\include\YDataType\YData.h"

#include <memory.h>
#include <sstream>

using namespace YLR;

YData::YData() :
	_type(YData::YInt),
	str(NULL)
{
}

YData::YData(const bool &b)
{
	//设置存储空间
	this->setSize(sizeof(b));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&b,this->getSize());
	setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YBool;
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

YData::YData(const YData &item) : YByteType(item)
{
	this->_type = item._type;
	this->str = NULL;
}

YData::~YData()
{
	if(this->str != NULL)
	{
		delete this->str;
	}
}

YData::DataType YData::getDataType() const
{
	return this->_type;
}

void YData::setNull()
{
	this->setSize();
}

bool YData::isNull() const
{
	if(this->getSize() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void YData::setFrom(const bool &b)
{
	//设置存储空间
	this->setSize(sizeof(b));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&b,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YBool;
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
	case YData::YBool:
		{
			bool b;
			YBYTE * buf = new YBYTE[sizeof(bool)];
			this->getData(buf,sizeof(bool));
			memcpy(&b,buf,sizeof(bool));
			delete[] buf;
			if(b)
			{
				data = 1;
			}
			else
			{
				data = 0;
			}
		}
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
	case YData::YBool:
		{
			bool b;
			YBYTE * buf = new YBYTE[sizeof(bool)];
			this->getData(buf,sizeof(bool));
			memcpy(&b,buf,sizeof(bool));
			delete[] buf;
			if(b)
			{
				data = 1.0;
			}
			else
			{
				data = 0.0;
			}
		}
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
	case YData::YBool:
		{
			bool b;
			YBYTE * buf = new YBYTE[sizeof(bool)];
			this->getData(buf,sizeof(bool));
			memcpy(&b,buf,sizeof(bool));
			delete[] buf;
			if(b)
			{
				data = 1.0;
			}
			else
			{
				data = 0.0;
			}
		}
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

const std::string * YData::toString()
{
	if(this->str != NULL)
	{
		delete this->str;
	}
	this->str = new std::string();

	switch(this->_type)
	{
	case YData::YBool:
		{
			bool b;
			YBYTE * buf = new YBYTE[sizeof(bool)];
			this->getData(buf,sizeof(bool));
			memcpy(&b,buf,sizeof(bool));
			delete[] buf;
			if(b)
			{
				*this->str = "true";
			}
			else
			{
				*this->str = "false";
			}
		}
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

YData & YData::operator=(const YData &item)
{
	YByteType::operator=(item);
	this->_type = item._type;
	this->str = NULL;
	return *this;
}