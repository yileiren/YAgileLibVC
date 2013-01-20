#include "../../include/YDataBase/YAccessDataBase.h"

using namespace YLR;

YAccessDataBase::YAccessDataBase() :
	_filePath(new std::string("")),
	_password(new std::string("")),
	_errorText(new std::string("")),
	_dataBaseType(YDataInterface::Access),
	_connection(new _ConnectionPtr())
{
}

YAccessDataBase::YAccessDataBase(const YAccessDataBase & item)
{
	this->_filePath = new std::string(*item._filePath);
	this->_password = new std::string(*item._password);
	this->_errorText = new std::string(*item._errorText);
	this->_dataBaseType = item._dataBaseType;
	this->_connection = new _ConnectionPtr();
}

YAccessDataBase::~YAccessDataBase()
{
	delete this->_filePath;
	delete this->_password;
	delete this->_errorText;
	delete this->_connection;
}

YAccessDataBase & YAccessDataBase::operator=(const YAccessDataBase & item)
{
	delete this->_filePath;
	delete this->_password;
	delete this->_errorText;
	delete this->_connection;

	this->_filePath = new std::string(*item._filePath);
	this->_password = new std::string(*item._password);
	this->_errorText = new std::string(*item._errorText);
	this->_dataBaseType = item._dataBaseType;
	this->_connection = new _ConnectionPtr();

	return *this;
}

void YAccessDataBase::setFilePath(const std::string & path)
{
	*this->_filePath = path;
}

const std::string * YAccessDataBase::getFilePath() const
{
	return this->_filePath;
}

void YAccessDataBase::setPassword(const std::string & password)
{
	*this->_password = password;
}

const std::string * YAccessDataBase::getPassword() const
{
	return this->_password;
}

const std::string *  YAccessDataBase::errorMessage()
{
	return this->_errorText;
}

YDataInterface::DataBaseType YAccessDataBase::databaseType()
{
	return this->_dataBaseType;
}

bool YAccessDataBase::connectDataBase()
{
	if(FAILED((*this->_connection).CreateInstance("ADODB.Connection")))
	{
		*this->_errorText = "创建接口失败！";
		return false;
	}

	//拼接数据库连接字符串。
	std::string connectString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=";
	connectString += *this->_filePath;
	connectString += ";Jet OLEDB:Database Password=" + *this->_password;

	//连接数据库
	if(FAILED((*this->_connection)->Open(connectString.c_str(),"","",-1)))
	{
		*this->_errorText = "打开数据库连接失败！";
		(*this->_connection).Release();
		return false;
	}
	return true;
}

bool YAccessDataBase::disconnectDataBase()
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

YDataInterface::ConnectState YAccessDataBase::connectState()
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

bool YAccessDataBase::beginTransaction()
{
	try
	{
		(*this->_connection)->BeginTrans();
		return true;
	}
	catch(_com_error er)
	{
		*this->_errorText =  "开启事务失败！";
		return false;
	}
}

bool YAccessDataBase::commitTransaction()
{
	try
	{
		(*this->_connection)->CommitTrans();
		return true;
	}
	catch(_com_error er)
	{
		*this->_errorText =  "提交事务失败！";
		return false;
	}
}

bool YAccessDataBase::rollbackTransaction()
{
	try
	{
		(*this->_connection)->RollbackTrans();
		return true;
	}
	catch(_com_error er)
	{
		*this->_errorText =  "回滚事务失败！";
		return false;
	}
}

const YDataTable * YAccessDataBase::executeSqlReturnDt(const std::string & sql)
{
	//获取数据集。
	_RecordsetPtr pRs;
	if(FAILED(pRs.CreateInstance(__uuidof(Recordset))))
	{
		*this->_errorText = "创建_RecordsetPtr接口失败！";
		return NULL;
	}
	try
	{
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
								int bInt = (int)pRs->Fields->GetItem(i)->Value;
								if(bInt != 0)
								{
									row.setData(i,YData(true));
								}
								else
								{
									row.setData(i,YData(false));
								}
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
	catch(_com_error er)
	{
		*this->_errorText =  "执行失败！";
		return NULL;
	}
}

bool YAccessDataBase::executeSqlWithOutDt(const std::string & sql)
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