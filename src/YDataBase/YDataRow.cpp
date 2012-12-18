#include "../../include/YDataBase/YDataRow.h"

using namespace YLR;

YDataRow::YDataRow() :
	_columns(new std::vector<YColumn>()),
	_datas(new std::vector<YData>)
{
}

YDataRow::YDataRow(const YDataRow & item)
{
	for(std::vector<YColumn>::size_type s = 0;s < item._columns->size();s++)
	{
		this->_columns->push_back(item._columns->at(s));
	}

	for(std::vector<YData>::size_type s = 0;s < item._datas->size();s++)
	{
		this->_datas->push_back(item._datas->at(s));
	}
}

YDataRow::~YDataRow()
{
	delete this->_columns;
	delete this->_datas;
}

YDataRow & YDataRow::operator=(const YDataRow & item)
{
	this->_columns->clear();
	for(std::vector<YColumn>::size_type s = 0;s < item._columns->size();s++)
	{
		this->_columns->push_back(item._columns->at(s));
	}

	this->_datas->clear();
	for(std::vector<YData>::size_type s = 0;s < item._datas->size();s++)
	{
		this->_datas->push_back(item._datas->at(s));
	}
	return *this;
}

void YDataRow::addColumn(const YColumn & column)
{
	this->_columns->push_back(column); //添加列。
	this->_datas->push_back(YData()); //添加数据。
}

void YDataRow::insertColumn(const int & index, const YColumn & column)
{
	//如果索引值不在范围内则不做任何操作。
	if(index >= (int)this->_columns->size())
	{
		this->_columns->push_back(YColumn()); //在行末尾新增一个空列。
		this->_datas->push_back(YData()); //在行末尾新增一个空数据。
		for(std::vector<YColumn>::size_type s = this->_columns->size() - 1;s > (std::vector<YColumn>::size_type)index;s--)
		{
			this->_columns->at(s) = this->_columns->at(s - 1);
			this->_datas->at(s) = this->_datas->at(s - 1);
		}
	}
	this->_columns->at(index) = column;
	this->_datas->at(index) = YData();
}

void YDataRow::removeColumn(const int & index)
{
	//如果索引值不在范围内则不做任何操作。
	if(index >= (int)this->_columns->size())
	{
		for(std::vector<YColumn>::size_type s = index;s < this->_columns->size() - 1;s++)
		{
			this->_columns->at(s) = this->_columns->at(s + 1);
			this->_datas->at(s) = this->_datas->at(s + 1);
		}

		this->_columns->pop_back();
		this->_datas->pop_back();
	}
}

const YColumn * YDataRow::getColumn(const int & index)
{
	if(index >= (int)this->_columns->size())
	{
		return &this->_columns->at(index);
	}
	else
	{
		return NULL;
	}
}

void YDataRow::setColumn(const int & index, const YColumn & column)
{
	if(index >= (int)this->_columns->size())
	{
		this->_columns->at(index) = column;
	}
}

const YData * YDataRow::getData(const int & index) const
{
	if(index >= (int)this->_columns->size())
	{
		return &this->_datas->at(index);
	}
	else
	{
		return NULL;
	}
}

const YData * YDataRow::getData(const std::string & physicaName) const
{
	for(std::vector<YColumn>::size_type s = 0;s < this->_columns->size();s++)
	{
		if(*this->_columns->at(s).getPhysicaName() == physicaName)
		{
			return this->getData((int)s);
		}
	}

	return NULL;
}

void YDataRow::setData(const int & index, const YData & data)
{
	if(index >= (int)this->_columns->size())
	{
		this->_datas->at(index) = data;
	}
}

void YDataRow::setData(const std::string & physicaName, const YData & data)
{
	for(std::vector<YColumn>::size_type s = 0;s < this->_columns->size();s++)
	{
		if(*this->_columns->at(s).getPhysicaName() == physicaName)
		{
			return this->setData((int)s,data);
		}
	}
}