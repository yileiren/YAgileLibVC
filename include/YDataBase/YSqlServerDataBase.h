#ifndef Y_SQLSERVER_DATABASE
#define Y_SQLSERVER_DATABASE

#include "YDataInterface.h"

namespace YLR
{
	/*!
	 * \brief
	 * SqlServer数据库访问类，用来连接SqlServer数据库。
	 * 数据库访问时使用微软ADO，注意初始化COM组件。
	 * 作者：董帅 创建时间：2013-1-8 9:43:09
	 */
	class YDATABASE_API YSqlServerDataBase : public YDataInterface
	{
	public:
		/*!
		 * \brief
		 * 默认构造函数。
		 */
		YSqlServerDataBase();

		/*!
		 * \brief
		 * 拷贝构造函数。
		 */
		YSqlServerDataBase(const YSqlServerDataBase & item);

		/*!
		 * \brief
		 * 析构函数。
		 */
		~YSqlServerDataBase();

		/*!
		 * \brief
		 * 赋值操作符重载。
		 */
		YSqlServerDataBase & operator=(const YSqlServerDataBase & item);

		/*!
		 * \brief
		 * 设置数据库名称。
		 * 作者：董帅 创建时间：2013-1-8 11:21:38
		 * 
		 * \param name 数据库名称。
		 */
		void setDataBaseName(const std::string & name);

		/*!
		 * \brief
		 * 获取数据库名称。
		 * 作者：董帅 创建时间：2013-1-8 11:30:27
		 *
		 * return 数据库名称。
		 */
		const std::string * getDataBaseName() const;

		/*!
		 * \brief
		 * 设置服务器名称。
		 * 作者：董帅 创建时间：2013-1-8 11:32:02
		 * 
		 * \param name 服务器名称。
		 */
		void setServerName(const std::string & name);

		/*!
		 * \brief
		 * 获取服务器名称。
		 * 作者：董帅 创建时间：2013-1-8 11:33:30
		 *
		 * \return 服务器名称。
		 */
		const std::string * getServerName() const;

		/*!
		 * \brief
		 * 设置数据库端口号。
		 * 作者：董帅 创建时间：2013-1-8 11:35:46
		 * 
		 * \param port 端口号。
		 */
		void setPort(const int & port);

		/*!
		 * \brief
		 * 获取端口号。
		 * 作者：董帅 创建时间：2013-1-8 11:37:27
		 *
		 * \return 端口号
		 */
		int getPort() const;

		/*!
		 * \brief
		 * 设置实例名。
		 * 作者：董帅 创建时间：2013-1-8 11:38:47
		 *
		 * \param example 实例名。
		 */
		void setExample(const std::string & example);

		/*!
		 * \brief
		 * 获取实例名。
		 * 作者：董帅 创建时间：2013-1-8 11:40:08
		 *
		 * \return 实例名。
		 */
		const std::string * getExample() const;

		/*!
		 * \brief
		 * 设置数据库访问用户id。
		 * 作者：董帅 创建时间：2013-1-8 13:41:34
		 *
		 * \param id 用户id
		 */
		void setUserID(const std::string & id);

		/*!
		 * \brief
		 * 获取数据库访问用户id。
		 * 作者：董帅 创建时间：2013-1-8 13:43:02
		 *
		 * \return 用户id。
		 */
		const std::string * getUserID() const;

		/*!
		 * \brief
		 * 设置数据库用户访问密码。
		 * 作者：董帅 创建时间：2013-1-8 13:44:33
		 *
		 * \param pass 访问密码。
		 */
		void setUserPassword(const std::string & pass);

		/*!
		 * \brief
		 * 获取数据库用户访问密码。
		 * 作者：董帅 创建时间：2013-1-8 13:46:00
		 *
		 * \return 用户访问密码。
		 */
		const std::string * getUserPassword() const;

		/*!
		 * \brief
		 * 获取数据库类型。
		 * 作者：董帅 创建时间：2013-1-8 13:47:47
		 *
		 * \return 数据库类型。
		 */
		virtual DataBaseType databaseType();

		/*!
		 * \brief
		 * 获取上次操作的错误信息。
		 * 作者：董帅 创建时间：2013-1-8 13:48:58
		 *
		 * \return 错误信息。
		 */
		virtual const std::string * errorMessage();

		/*!
		 * \brief
		 * 连接数据库。
		 * 作者：董帅 创建时间：2013-1-8 13:50:36
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool connectDataBase();

		/*!
		 * \brief
		 * 断开数据库连接。
		 * 作者：董帅 创建时间：2013-1-8 13:51:10
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool disconnectDataBase();

		/*!
		 * \brief
		 * 获取连接状态。
		 * 作者：董帅 创建时间：2013-1-8 13:51:45
		 *
		 * \return 连接转台。
		 */
		virtual ConnectState connectState();

		/*!
		 * \brief
		 * 开启数据库事务。
		 * 作者：董帅 创建时间：2013-1-8 13:52:25
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool beginTransaction();

		/*!
		 * \brief
		 * 提交事务。
		 * 作者：董帅 创建时间：2013-1-8 13:53:45
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool commitTransaction();

		/*!
		 * \brief
		 * 回滚事务。
		 * 作者：董帅 创建时间：2013-1-8 13:54:50
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool rollbackTransaction();

		/*!
		 * \brief
		 * 实行SQL语句，返回数据，使用结束注意释放数据。
		 * 作者：董帅 创建时间：2013-1-8 13:55:19
		 *
		 * \param sql 要执行的SQL语句。
		 *
		 * \return 返回数据，失败返回NULL。
		 */
		virtual YDataTable * executeSqlReturnDt(const std::string & sql);

		/*!
		 * \brief
		 * 执行没有数据返回的sql语句。
		 * 作者：董帅 创建时间：2013-1-8 13:56:03
		 *
		 * \param sql 要执行的SQL语句。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool executeSqlWithOutDt(const std::string & sql);
	private:
		DataBaseType _dataBaseType; /*!< 数据库类型。 */
		ConnectState _connectState; /*!< 连接状态。 */
		std::string * _errorText; /*!< 最后一次操作的错误信息。 */

		std::string * _dataBaseName; /*!< 数据库名称。 */
		std::string * _serverName; /*!< 服务器名称。 */
		int _port; /*!< 端口号。 */
		std::string * _example; /*!< 实例名称。 */
		std::string * _userID; /*!< 用户id。 */
		std::string * _userPassword; /*!< 用户密码。 */
	};
}

#endif