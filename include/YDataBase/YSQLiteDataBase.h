#ifndef Y_SQLITE_DATABASE
#define Y_SQLITE_DATABASE

#include "YDataInterface.h"
#include "../../sqlite3/sqlite3.h"

namespace YLR
{
	/*!
	 * \brief
	 * SQLite数据库访问类。
	 * 作者：董帅 创建时间：2013-1-21 13:16:46
	 */
	class YSQLiteDataBase : public  YDataInterface
	{
	public:
		/*!
		 * \brief
		 * 默认构造函数。
		 */
		YSQLiteDataBase();

		/*!
		 * \brief
		 * 拷贝构造函数。
		 */
		YSQLiteDataBase(const YSQLiteDataBase & item);

		/*!
		 * \brief
		 * 析构函数。
		 */
		~YSQLiteDataBase();

		/*!
		 * \brief
		 * 赋值操作符重载。
		 */
		YSQLiteDataBase & operator=(const YSQLiteDataBase & item);
		
		/*!
		 * \brief
		 * 设置文件路径。
		 * 作者：董帅 创建时间：2013-1-21 13:22:18
		 *
		 * \param path 文件路径。
		 */
		void setFilePath(const std::string & path);

		/*!
		 * \brief
		 * 获取文件路径。
		 * 作者：董帅 创建时间：2013-1-21 13:23:37
		 *
		 * \return 文件路径。
		 */
		const std::string * getFilePath() const;

		/*!
		 * \brief
		 * 获取数据库类型。
		 * 作者：董帅 创建时间：2013-1-21 13:25:11
		 *
		 * \return 数据库类型。
		 */
		virtual DataBaseType databaseType();

		/*!
		 * \brief
		 * 获取上次操作的错误信息。
		 * 作者：董帅 创建时间：2013-1-21 13:26:59
		 *
		 * \return 错误信息。
		 */
		virtual const std::string * errorMessage();

		/*!
		 * \brief
		 * 连接数据库。
		 * 作者：董帅 创建时间：2013-1-21 13:27:28
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool connectDataBase();

		/*!
		 * \brief
		 * 断开数据库连接。
		 * 作者：董帅 创建时间：2013-1-21 13:35:27
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool disconnectDataBase();

		/*!
		 * \brief
		 * 获取连接状态。
		 * 作者：董帅 创建时间：2013-1-21 13:45:14
		 *
		 * \return 连接转台。
		 */
		virtual ConnectState connectState();

		/*!
		 * \brief
		 * 开启数据库事务。
		 * 作者：董帅 创建时间：2013-1-21 13:49:34
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool beginTransaction();

		/*!
		 * \brief
		 * 提交事务。
		 * 作者：董帅 创建时间：2013-1-21 13:52:02
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool commitTransaction();

		/*!
		 * \brief
		 * 回滚事务。
		 * 作者：董帅 创建时间：2013-1-21 13:55:39
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool rollbackTransaction();

		/*!
		 * \brief
		 * 实行SQL语句，返回数据，使用结束注意释放数据。
		 * 作者：董帅 创建时间：2013-1-7 16:11:02
		 *
		 * \param sql 要执行的SQL语句。
		 *
		 * \return 返回数据，失败返回NULL，返回的数据集使用YLR::YDataInterface::releaseDataTable方法释放。
		 */
		virtual const YDataTable * executeSqlReturnDt(const std::string & sql)  = 0;

		/*!
		 * \brief
		 * 执行没有数据返回的sql语句。
		 * 作者：董帅 创建时间：2013-1-7 16:13:18
		 *
		 * \param sql 要执行的SQL语句。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool executeSqlWithOutDt(const std::string & sql)  = 0;
	private:
		YDataInterface::DataBaseType _databaseType; /*!< 数据库类型。 */
		YDataInterface::ConnectState _connectState; /*!< 连接类型。 */

		std::string * _filePath; /*!< 文件存储路径。 */

		sqlite3 * _db; /*!< 数据库指针。 */
		std::string * _errorText; /*!< 错误信息。 */
	};
}

#endif