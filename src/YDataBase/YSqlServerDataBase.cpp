#include "../../include/YDataBase/YSqlServerDataBase.h"

using namespace YLR;

YSqlServerDataBase::YSqlServerDataBase() :
	_dataBaseType(YDataInterface::MSSQL),
	_connectState(YDataInterface::Disconnected),
	_errorText(new std::string("")),
	_dataBaseName(new std::string("")),
	_serverName(new std::string("localhost")),
	_port(1433),
	_example(new std::string("")),
	_userID(new std::string("sa")),
	_userPassword(new std::string(""))
{
}

YSqlServerDataBase::YSqlServerDataBase(const YSqlServerDataBase & item)
{
	this->_dataBaseType = item._dataBaseType;
	this->_connectState = item._connectState;
	this->_errorText = new std::string(*item._errorText);
	this->_dataBaseName = new std::string(*item._dataBaseName);
	this->_serverName = new std::string(*item._serverName);
	this->_port = item._port;
	this->_example = new std::string(*item._example);
	this->_userID = new std::string(*item._userID);
	this->_userPassword = new std::string(*item._userPassword);
}

YSqlServerDataBase::~YSqlServerDataBase()
{
	delete this->_errorText;
	delete this->_dataBaseName;
	delete this->_serverName;
	delete this->_example;
	delete this->_userID;
	delete this->_userPassword;
}

YSqlServerDataBase & YSqlServerDataBase::operator=(const YSqlServerDataBase & item)
{
	delete this->_errorText;
	delete this->_dataBaseName;
	delete this->_serverName;
	delete this->_example;
	delete this->_userID;
	delete this->_userPassword;

	this->_dataBaseType = item._dataBaseType;
	this->_connectState = item._connectState;
	this->_errorText = new std::string(*item._errorText);
	this->_dataBaseName = new std::string(*item._dataBaseName);
	this->_serverName = new std::string(*item._serverName);
	this->_port = item._port;
	this->_example = new std::string(*item._example);
	this->_userID = new std::string(*item._userID);
	this->_userPassword = new std::string(*item._userPassword);
	return *this;
}

void YSqlServerDataBase::setDataBaseName(const std::string & name)
{
	*this->_dataBaseName = name;
}

const std::string * YSqlServerDataBase::getDataBaseName() const
{
	return this->_dataBaseName;
}

void YSqlServerDataBase::setServerName(const std::string & name)
{
	*this->_serverName = name;
}

const std::string * YSqlServerDataBase::getServerName() const
{
	return this->_serverName;
}

void YSqlServerDataBase::setPort(const int & port)
{
	this->_port = port;
}

int YSqlServerDataBase::getPort() const
{
	return this->_port;
}

void YSqlServerDataBase::setExample(const std::string & example)
{
	*this->_example = example;
}

const std::string * YSqlServerDataBase::getExample() const
{
	return this->_example;
}

void YSqlServerDataBase::setUserID(const std::string & id)
{
	*this->_userID = id;
}

const std::string * YSqlServerDataBase::getUserID() const
{
	return this->_userID;
}

void YSqlServerDataBase::setUserPassword(const std::string & pass)
{
	*this->_userPassword;
}

const std::string * YSqlServerDataBase::getUserPassword() const
{
	return this->_userPassword;
}

YDataInterface::DataBaseType YSqlServerDataBase::databaseType()
{
	return this->_dataBaseType;
}

const std::string * YSqlServerDataBase::errorMessage()
{
	return this->_errorText;
}

bool YSqlServerDataBase::connectDataBase()
{
	return false;
}

bool YSqlServerDataBase::disconnectDataBase()
{
	return false;
}

YDataInterface::ConnectState YSqlServerDataBase::connectState()
{
	return this->_connectState;
}

bool YSqlServerDataBase::beginTransaction()
{
	return false;
}

bool YSqlServerDataBase::commitTransaction()
{
	return false;
}

bool YSqlServerDataBase::rollbackTransaction()
{
	return false;
}

YDataTable * YSqlServerDataBase::executeSqlReturnDt(const std::string & sql)
{
	return NULL;
}

bool YSqlServerDataBase::executeSqlWithOutDt(const std::string & sql)
{
	return false;
}