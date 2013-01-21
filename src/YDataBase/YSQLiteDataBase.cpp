#include "../../include/YDataBase/YSQLiteDataBase.h"

using namespace YLR;

YSQLiteDataBase::YSQLiteDataBase() :
	_databaseType(YDataInterface::SQLite),
	_filePath(new std::string("")),
	_errorText(new std::string("")),
	_connectState(YDataInterface::Disconnected)
{
}

YSQLiteDataBase::YSQLiteDataBase(const YSQLiteDataBase & item)
{
	this->_databaseType = item._databaseType;
	this->_connectState = YDataInterface::Disconnected;
	this->_filePath = new std::string(*item._filePath);
	this->_errorText = new std::string(*item._errorText);
}

YSQLiteDataBase::~YSQLiteDataBase()
{
	delete this->_filePath;
	delete this->_errorText;
}

YSQLiteDataBase & YSQLiteDataBase::operator=(const YSQLiteDataBase & item)
{
	this->_databaseType = item._databaseType;
	this->_connectState = YDataInterface::Disconnected;
	this->_filePath = new std::string(*item._filePath);
	this->_errorText = new std::string(*item._errorText);

	return *this;
}

void YSQLiteDataBase::setFilePath(const std::string & path)
{
	*this->_filePath = path;
}

const std::string * YSQLiteDataBase::getFilePath() const
{
	return this->_filePath;
}

YDataInterface::DataBaseType YSQLiteDataBase::databaseType()
{
	return this->_databaseType;
}

const std::string * YSQLiteDataBase::errorMessage()
{
	return this->_errorText;
}

bool YSQLiteDataBase::connectDataBase()
{
	int rc = sqlite3_open(this->_filePath->c_str(),&this->_db);

	if(rc)
	{
		sqlite3_close(this->_db);
		*this->_errorText = "打开数据库失败！||" + std::string(sqlite3_errmsg(this->_db));
		return false;
	}
	else
	{
		this->_connectState = YDataInterface::Connected;
		return true;
	}
}

bool YSQLiteDataBase::disconnectDataBase()
{
	int rc = sqlite3_close(this->_db);

	if(rc)
	{
		return false;
	}
	else
	{
		this->_connectState = YDataInterface::Disconnected;
		return true;
	}
		
}

YDataInterface::ConnectState YSQLiteDataBase::connectState()
{
	return this->_connectState;
}

bool YSQLiteDataBase::beginTransaction()
{
	char * zErr;
	int rc = sqlite3_exec(this->_db,"BEGIN",NULL,NULL,&zErr);

	if(rc)
	{
		*this->_errorText = "开启事务失败！||" + std::string(zErr);
		sqlite3_free(zErr);
		return false;
	}
	else
	{
		return true;
	}
}

bool YSQLiteDataBase::commitTransaction()
{
	char * zErr;
	int rc = sqlite3_exec(this->_db,"COMMIT",NULL,NULL,&zErr);

	if(rc)
	{
		*this->_errorText = "提交事务失败！||" + std::string(zErr);
		sqlite3_free(zErr);
		return false;
	}
	else
	{
		return true;
	}
}

bool YSQLiteDataBase::rollbackTransaction()
{
	char * zErr;
	int rc = sqlite3_exec(this->_db,"ROLLBACK",NULL,NULL,&zErr);

	if(rc)
	{
		*this->_errorText = "回滚事务失败！||" + std::string(zErr);
		sqlite3_free(zErr);
		return false;
	}
	else
	{
		return true;
	}
}

const YDataTable * YSQLiteDataBase::executeSqlReturnDt(const std::string & sql)
{
	YDataTable *table = NULL;
	sqlite3_stmt *stmt;

	int rc = sqlite3_prepare_v2(this->_db,sql.c_str(),strlen(sql.c_str()),&stmt,NULL);
	if(rc)
	{
		*this->_errorText = "获取数据失败！||" + std::string(sqlite3_errmsg(this->_db));
	}
	else
	{
		table = new YDataTable();

		int columnCount = sqlite3_column_count(stmt);
		for(int i = 0;i < columnCount;i++)
		{
			YColumn column;
			column.setPhysicaName(std::string(sqlite3_column_name(stmt,i)));//数据库存储物理名称。
			table->addColumn(column);
		}

		rc = sqlite3_step(stmt);
		while(rc == SQLITE_ROW)
		{
			YDataRow row;
			for(int i = 0;i < columnCount;i++)
			{	
				row.addColumn(*table->getColumn(i));

				switch(sqlite3_column_type(stmt,i))
				{
				case SQLITE_INTEGER:
					{
						row.setData(i,YData(sqlite3_column_int(stmt,i)));
						break;
					}
				case SQLITE_FLOAT:
					{
						row.setData(i,YData(sqlite3_column_double(stmt,i)));
						break;
					}
				case SQLITE_TEXT:
					{
						row.setData(i,YData(std::string((char *)sqlite3_column_text(stmt,i))));
						break;
					}
				case SQLITE_NULL:
				default:
					{
						YData data;
						data.setNull();
						row.setData(i,data);
						break;
					}
				}
			}
			table->addRow(row);
			rc = sqlite3_step(stmt);
		}
	}

	return table;
}

bool YSQLiteDataBase::executeSqlWithOutDt(const std::string & sql)
{
	char *zErr;

	int rc = sqlite3_exec(this->_db,sql.c_str(),NULL,NULL,&zErr);
	if(rc != SQLITE_OK)
	{
		*this->_errorText = "执行语句失败！||" + std::string(zErr);
		sqlite3_free(zErr);
		return false;
	}

	return true;
}