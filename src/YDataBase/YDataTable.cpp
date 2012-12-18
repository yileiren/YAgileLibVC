#include "../../include/YDataBase/YDataTable.h"

using namespace YLR;

YDataTable::YDataTable() :
	_columns(new std::vector<YColumn>()),
	_rows(new std::vector<YDataRow>())
{
}

YDataTable::YDataTable(const YDataTable & item)
{
	for(std::vector<YColumn>::size_type s = 0;s < item._columns->size();s++)
	{
		this->_columns->push_back(item._columns->at(s));
	}

	for(std::vector<YDataRow>::size_type s = 0;s < item._rows->size();s++)
	{
		this->_rows->push_back(item._rows->at(s));
	}
}

YDataTable::~YDataTable()
{
	delete this->_columns;
	delete this->_rows;
}

YDataTable & YDataTable::operator=(const YDataTable & item)
{
	this->_columns->clear();
	for(std::vector<YColumn>::size_type s = 0;s < item._columns->size();s++)
	{
		this->_columns->push_back(item._columns->at(s));
	}

	this->_rows->clear();
	for(std::vector<YDataRow>::size_type s = 0;s < item._rows->size();s++)
	{
		this->_rows->push_back(item._rows->at(s));
	}
	return *this;
}

void YDataTable::addColumn(const YColumn & column)
{
	this->_columns->push_back(column); //添加列。
	//添加各数据行的列。
	for(std::vector<YDataRow>::size_type s = 0;s < this->_rows->size();s++)
	{
		this->_rows->at(s).addColumn(column);
	}
}

void YDataTable::insertColumn(const int & index, const YColumn & column)
{
	//如果索引值不在范围内则不做任何操作。
	if(index < (int)this->_columns->size())
	{
		this->_columns->push_back(YColumn()); //在行末尾新增一个空列。
		for(std::vector<YColumn>::size_type s = this->_columns->size() - 1;s > (std::vector<YColumn>::size_type)index;s--)
		{
			this->_columns->at(s) = this->_columns->at(s - 1);
		}

		//添加各数据行的列。
		for(std::vector<YDataRow>::size_type s = 0;s < this->_rows->size();s++)
		{
			this->_rows->at(s).insertColumn(index,column);
		}
	}
	this->_columns->at(index) = column;
}

void YDataTable::removeColumn(const int & index)
{
	//如果索引值不在范围内则不做任何操作。
	if(index < (int)this->_columns->size())
	{
		for(std::vector<YColumn>::size_type s = index;s < this->_columns->size() - 1;s++)
		{
			this->_columns->at(s) = this->_columns->at(s + 1);
		}

		this->_columns->pop_back();
		
		for(std::vector<YDataRow>::size_type s = 0;s < this->_rows->size();s++)
		{
			this->_rows->at(s).removeColumn(index);
		}
	}
}

const YColumn * YDataTable::getColumn(const int & index)
{
	if(index < (int)this->_columns->size())
	{
		return &this->_columns->at(index);
	}
	else
	{
		return NULL;
	}
}

void YDataTable::setColumn(const int & index, const YColumn & column)
{
	if(index < (int)this->_columns->size())
	{
		this->_columns->at(index) = column;
	}
}

void YDataTable::addRow(const YDataRow & row)
{
	this->_rows->push_back(row);
}

void YDataTable::insertRow(const int & index, const YDataRow & row)
{
	if(index < (int)this->_rows->size())
	{
		this->_rows->push_back(YDataRow()); //在行末尾新增一个空列。
		for(std::vector<YDataRow>::size_type s = this->_rows->size() - 1;
			s > (std::vector<YDataRow>::size_type)index;
			s--)
		{
			this->_rows->at(s) = this->_rows->at(s - 1);
		}
		this->_rows->at(index) = row;
	}
}

void YDataTable::removeRow(const int & index)
{
	//如果索引值不在范围内则不做任何操作。
	if(index < (int)this->_rows->size())
	{
		for(std::vector<YDataRow>::size_type s = index;
			s < this->_rows->size() - 1;
			s++)
		{
			this->_rows->at(s) = this->_rows->at(s + 1);
		}

		this->_rows->pop_back();
	}
}

const YDataRow * YDataTable::getRow(const int & index) const
{
	if(index < (int)this->_rows->size())
	{
		return &this->_rows->at(index);
	}
	else
	{
		return NULL;
	}
}

void YDataTable::setRow(const int & index, const YDataRow & row)
{
	if(index < (int)this->_rows->size())
	{
		this->_rows->at(index) = row;
	}
}

const YData * YDataTable::getData(const int & rowIndex, const int & columnIndex) const
{
	if(rowIndex < (int)this->_rows->size())
	{
		return this->_rows->at(rowIndex).getData(columnIndex);
	}
	else
	{
		return NULL;
	}
}

const YData * YDataTable::getData(const int & rowIndex, const std::string & physicaName) const
{
	if(rowIndex < (int)this->_rows->size())
	{
		return this->_rows->at(rowIndex).getData(physicaName);
	}
	else
	{
		return NULL;
	}
}

void YDataTable::setData(const int & rowIndex, const int & columnIndex, const YData & data)
{
	if(rowIndex < (int)this->_rows->size())
	{
		this->_rows->at(rowIndex).setData(columnIndex,data);
	}
}

void YDataTable::setData(const int & rowIndex, const std::string & physicaName, const YData & data)
{
	if(rowIndex < (int)this->_rows->size())
	{
		this->_rows->at(rowIndex).setData(physicaName,data);
	}
}