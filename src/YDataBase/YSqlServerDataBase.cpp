#include "../../include/YDataBase/YSqlServerDataBase.h"

using namespace YLR;

#include <sstream>

YSqlServerDataBase::YSqlServerDataBase() :
	_dataBaseType(YDataInterface::MSSQL),
	_errorText(new std::string("")),
	_dataBaseName(new std::string("")),
	_serverName(new std::string("localhost")),
	_port(1433),
	_example(new std::string("")),
	_userID(new std::string("sa")),
	_userPassword(new std::string("")),
	_connection(new _ConnectionPtr())
{
}

YSqlServerDataBase::YSqlServerDataBase(const YSqlServerDataBase & item)
{
	this->_dataBaseType = item._dataBaseType;
	this->_errorText = new std::string(*item._errorText);
	this->_dataBaseName = new std::string(*item._dataBaseName);
	this->_serverName = new std::string(*item._serverName);
	this->_port = item._port;
	this->_example = new std::string(*item._example);
	this->_userID = new std::string(*item._userID);
	this->_userPassword = new std::string(*item._userPassword);
	this->_connection = new _ConnectionPtr();
}

YSqlServerDataBase::~YSqlServerDataBase()
{
	delete this->_errorText;
	delete this->_dataBaseName;
	delete this->_serverName;
	delete this->_example;
	delete this->_userID;
	delete this->_userPassword;
	delete this->_connection;
}

YSqlServerDataBase & YSqlServerDataBase::operator=(const YSqlServerDataBase & item)
{
	delete this->_errorText;
	delete this->_dataBaseName;
	delete this->_serverName;
	delete this->_example;
	delete this->_userID;
	delete this->_userPassword;
	delete this->_connection;

	this->_dataBaseType = item._dataBaseType;
	this->_errorText = new std::string(*item._errorText);
	this->_dataBaseName = new std::string(*item._dataBaseName);
	this->_serverName = new std::string(*item._serverName);
	this->_port = item._port;
	this->_example = new std::string(*item._example);
	this->_userID = new std::string(*item._userID);
	this->_userPassword = new std::string(*item._userPassword);
	this->_connection = new _ConnectionPtr();
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
	*this->_userPassword = pass;
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
	if(FAILED((*this->_connection).CreateInstance("ADODB.Connection")))
	{
		*this->_errorText = "创建接口失败！";
		return false;
	}

	//拼接数据库连接字符串。
	std::string connectString = "Driver=SQL Server;Server=";
	connectString += *this->_serverName;

	std::stringstream stream;
	stream << this->_port;
	std::string sPort;
	stream >> sPort;
	connectString += "," + sPort;

	if(*this->_example != "")
	{
		connectString += "/" + *this->_example;
	}
	connectString += ";Database=" + *this->_dataBaseName;
	connectString += ";UID=" + *this->_userID;
	connectString += ";PWD=" + *this->_userPassword;

	//连接数据库
	if(FAILED((*this->_connection)->Open(connectString.c_str(),"","",-1)))
	{
		*this->_errorText = "打开数据库连接失败！";
		(*this->_connection).Release();
		return false;
	}
	return true;
}

bool YSqlServerDataBase::disconnectDataBase()
{
	if(adStateOpen == (*this->_connection)->State)
	{
		//断开数据库连接。
		if(FAILED((*this->_connection)->Close()))
		{
			*this->_errorText = "断开数据库连接失败！";
			return false;
		}

		(*this->_connection).Release();
	}
	return true;;
}

YDataInterface::ConnectState YSqlServerDataBase::connectState()
{
	if((*this->_connection)->State)
	{
		return YDataInterface::Connected;
	}
	else
	{
		return YDataInterface::Disconnected;
	}
}

bool YSqlServerDataBase::beginTransaction()
{
	(*this->_connection)->BeginTrans();
	return true;
}

bool YSqlServerDataBase::commitTransaction()
{
	(*this->_connection)->CommitTrans();
	return true;
}

bool YSqlServerDataBase::rollbackTransaction()
{
	(*this->_connection)->RollbackTrans();
	return true;
}

const YDataTable * YSqlServerDataBase::executeSqlReturnDt(const std::string & sql)
{
	//获取数据集。
	_RecordsetPtr pRs;
	if(FAILED(pRs.CreateInstance(__uuidof(Recordset))))
	{
		*this->_errorText = "创建_RecordsetPtr接口失败！";
		return NULL;
	}
	pRs->Open(sql.c_str(),(*this->_connection).GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	
	YDataTable *table = NULL;
	if(pRs != NULL)
	{

		pRs->MoveFirst();
		//构建表格字段信息
		table = new YDataTable();
		for(long i = 0;i < pRs->Fields->Count;i++)
		{
			YColumn column;
			column.setPhysicaName(std::string(pRs->Fields->GetItem(i)->GetName()));//数据库存储物理名称。
			table->addColumn(column);
		}

		while(!pRs->adoEOF)
		{
			YDataRow row;
			for(long i = 0;i < pRs->Fields->Count;i++)
			{
				row.addColumn(*table->getColumn(i));
				//设置数据类型。
				if(pRs->Fields->GetItem(i)->GetValue().vt != VT_NULL)
				{
					switch (pRs->Fields->GetItem(i)->GetType())
					{
					case adBSTR: //字符串
					case adChar:
					case adDate:
					case adDBDate:   
					case adDBTime:
					case adDBTimeStamp:
					case adLongVarChar:  
					case adLongVarWChar: 
					case adVarChar:
					case adVarWChar:
					case adWChar:
						{
							long lDataLength = pRs->Fields->GetItem(i)->GetActualSize();
							
							std::string s = "";
							if(lDataLength > 0)
							{
								_bstr_t ret(pRs->Fields->GetItem(i)->Value);
								s = ret;
							}

							row.setData(i,YData(s));
							break;
						}
					case adBigInt:
					case adInteger:
					case adTinyInt:
					case adUnsignedBigInt:
					case adUnsignedInt:
					case adUnsignedSmallInt:
					case adUnsignedTinyInt:
						{
							row.setData(i,YData((int)pRs->Fields->GetItem(i)->GetValue()));
							break;
						}
					case adCurrency:
					case adDouble:
					case adNumeric:
					case adSingle:
						{
							row.setData(i,YData((double)pRs->Fields->GetItem(i)->GetValue()));
							break;
						}
					case adBoolean:   //布尔型  
						{
							row.setData(i,YData((bool)pRs->Fields->GetItem(i)->GetValue()));
							break;
						}
					default:
						{
							YData data;
							data.setNull();
							row.setData(i,data);
							break;
						}
					}
				}
				else
				{
					YData data;
					data.setNull();
					row.setData(i,data);
				}
			}

			table->addRow(row);
			pRs->MoveNext();
		}
	}

	pRs->Close();
	//pRs->Release();

	return table;
}

bool YSqlServerDataBase::executeSqlWithOutDt(const std::string & sql)
{
	_CommandPtr objCommand;//执行对象

	//创建执行接口
	if (FAILED(objCommand.CreateInstance("ADODB.Command")))
	{
		*this->_errorText = "创建执行接口失败！";
		return false;
	}
	
	try
	{
		_variant_t vNULL;
		vNULL.vt = VT_ERROR;
		vNULL.scode = DISP_E_PARAMNOTFOUND;///定义为无参数
		objCommand->ActiveConnection = *this->_connection;///非常关键的一句，将建立的连接赋值给它

		objCommand->CommandText = sql.c_str();
		
		objCommand->Execute(&vNULL,&vNULL,adCmdText);
		return true;
	}
	catch(_com_error er)
	{
		*this->_errorText =  "执行失败！";
		return false;
	}
}