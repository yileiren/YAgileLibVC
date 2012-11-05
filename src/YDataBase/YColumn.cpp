#include "../../include/YDataBase/YColumn.h"

using namespace YLR;

YColumn::YColumn() :
	_physicaName(NULL),
	_logicalName(NULL),
	_dataType(YData::YInt)
{
	//初始化数据。
}

YColumn::YColumn(const std::string & physicaName, const std::string & logicalName, const YData::DataType & dataType)
{
	//使用参数初始化。
	this->_physicaName = new std::string(physicaName);
	this->_logicalName = new std::string(logicalName);
	this->_dataType = dataType;
}

YColumn::YColumn(const YColumn & item)
{
	//使用对象初始化数据。
	this->_physicaName = new std::string(*item._physicaName);
	this->_logicalName = new std::string(*item._logicalName);
	this->_dataType = item._dataType;
}

YColumn::~YColumn()
{
	//释放对象所有资源。
	if(this->_physicaName != NULL)
	{
		delete this->_physicaName;
	}

	if(this->_logicalName != NULL)
	{
		delete this->_logicalName;
	}
}

YColumn & YColumn::operator=(const YColumn & item)
{
	//释放原有资源
	if(this->_physicaName != NULL)
	{
		delete this->_physicaName;
	}

	if(this->_logicalName != NULL)
	{
		delete this->_logicalName;
	}

	this->_physicaName = new std::string(*item._physicaName);
	this->_logicalName = new std::string(*item._logicalName);
	this->_dataType = item._dataType;

	return *this;
}

void YColumn::setPhysicaName(const std::string & physicaName)
{
	//释放原有空间
	if(this->_physicaName != NULL)
	{
		delete this->_physicaName;
	}
	this->_physicaName = new std::string(physicaName);
}

const std::string * YColumn::getPhysicaName() const
{
	return this->_physicaName;
}

void YColumn::setLogicalName(const std::string & logicalName)
{
	//释放原有空间
	if(this->_logicalName != NULL)
	{
		delete this->_logicalName;
	}
	this->_logicalName = new std::string(logicalName);
}

const std::string * YColumn::getLogicalName() const
{
	return this->_logicalName;
}

void YColumn::setDataType(const YData::DataType & dataType)
{
	this->_dataType = dataType;
}

const YData::DataType YColumn::getDataType() const
{
	return this->_dataType;
}