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
		this->_connectState = YDataInterface::Disconnected;
		return true;
	}
	else
		return false;
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
		return true;
	}
	else
	{
		*this->_errorText = "开启事务失败！||" + std::string(zErr);
		return false;
	}
}

bool YSQLiteDataBase::commitTransaction()
{
	char * zErr;
	int rc = sqlite3_exec(this->_db,"COMMIT",NULL,NULL,&zErr);

	if(rc)
	{
		return true;
	}
	else
	{
		*this->_errorText = "提交事务失败！||" + std::string(zErr);
		return false;
	}
}

bool YSQLiteDataBase::rollbackTransaction()
{
	char * zErr;
	int rc = sqlite3_exec(this->_db,"ROLLBACK",NULL,NULL,&zErr);

	if(rc)
	{
		return true;
	}
	else
	{
		*this->_errorText = "回滚事务失败！||" + std::string(zErr);
		return false;
	}
}