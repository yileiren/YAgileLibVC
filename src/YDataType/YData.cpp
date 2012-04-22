#include "..\..\include\YDataType\YData.h"

#include <memory.h>

using namespace YLR;

YData::YData() :
	_type(YData::YNull)
{
}

YData::YData(const int &d)
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

YData::YData(const double &d)
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

YData::YData(const float &d)
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

YData::YData(const std::string &d)
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
	//设置存储空间
	this->setSize(sizeof(d));

	//复制数据
	YBYTE * buf = new YBYTE[this->getSize()];
	memcpy(buf,&d,this->getSize());
	this->setData(buf,this->getSize());
	delete[] buf;
	this->_type = YData::YString;
}

int YData::toInt() const
{
	int data = 0;

	YBYTE * buf = new YBYTE[sizeof(int)];
	this->getData(buf,sizeof(int));
	memcpy(&data,buf,sizeof(int));

	return data;
}