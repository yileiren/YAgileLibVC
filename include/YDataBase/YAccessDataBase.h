#ifndef Y_ACCESS_DATABASE
#define Y_ACCESS_DATABASE

#include "YDataInterface.h"
#include "ado\MSAdo.h"

/*!
 * \brief
 * 异类人VC敏捷开发库。
 */
namespace YLR
{
/*!
 * \brief
 * 数据库操作类库。
 */
namespace YDataBase
{
	/*!
	 * \brief
	 * Access数据库访问类。
	 * 作者：董帅 创建时间：2013-2-27 14:28:28
	 */
	class YDATABASE_API YAccessDataBase : public YDataInterface
	{
	public:
		/*!
		 * \brief
		 * 默认构造函数。
		 */
		YAccessDataBase();

		/*!
		 * \brief
		 * 拷贝构造函数。
		 */
		YAccessDataBase(const YAccessDataBase & item);

		/*!
		 * \brief
		 * 析构函数。
		 */
		~YAccessDataBase();

		/*!
		 * \brief
		 * 赋值操作符重载。
		 * 作者：董帅 创建时间：2013-1-20 14:14:54
		 *
		 * \item 源操作数。
		 */
		YAccessDataBase & operator=(const YAccessDataBase & item);

		/*!
		 * \brief
		 * 设置文件完整路径。
		 * 作者：董帅 创建时间：2013-1-20 14:18:28
		 *
		 * \param path 文件完整路径。
		 */
		void setFilePath(const std::string & path);

		/*!
		 * \brief
		 * 获取文件完整路径。
		 * 作者：董帅 创建时间：2013-1-20 14:22:12
		 *
		 * \return 文件完整路径。
		 */
		const std::string * getFilePath() const;

		/*!
		 * \brief
		 * 设置密码。
		 * 作者：董帅 创建时间：2013-1-20 14:24:53
		 *
		 * \param password 密码。
		 */
		void setPassword(const std::string & password);

		/*!
		 * \brief
		 * 获取密码。
		 * 作者：董帅 创建时间：顶级
		 *
		 * \return 密码。
		 */
		const std::string * getPassword() const;

		/*!
		 * \brief
		 * 获取数据库类型。
		 * 作者：董帅 创建时间：2013-1-20 14:37:29
		 *
		 * \return 数据库类型。
		 */
		virtual DataBaseType databaseType();

		/*!
		 * \brief
		 * 获取上次操作的错误信息。
		 * 作者：董帅 创建时间：2013-1-20 14:34:16
		 *
		 * \return 错误信息。
		 */
		virtual const std::string * errorMessage();

		/*!
		 * \brief
		 * 连接数据库。
		 * 作者：董帅 创建时间：2013-1-20 14:38:42
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool connectDataBase();

		/*!
		 * \brief
		 * 断开数据库连接。
		 * 作者：董帅 创建时间：2013-1-20 15:05:54
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool disconnectDataBase();

		/*!
		 * \brief
		 * 获取连接状态。
		 * 作者：董帅 创建时间：2013-1-20 15:07:46
		 *
		 * \return 连接转台。
		 */
		virtual ConnectState connectState();

		/*!
		 * \brief
		 * 开启数据库事务。
		 * 作者：董帅 创建时间：2013-1-20 15:08:40
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool beginTransaction();

		/*!
		 * \brief
		 * 提交事务。
		 * 作者：董帅 创建时间：2013-1-20 15:09:49
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool commitTransaction();

		/*!
		 * \brief
		 * 回滚事务。
		 * 作者：董帅 创建时间：2013-1-20 15:11:02
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool rollbackTransaction();

		/*!
		 * \brief
		 * 实行SQL语句，返回数据，使用结束注意释放数据。
		 * 作者：董帅 创建时间：2013-1-20 15:11:38
		 *
		 * \param sql 要执行的SQL语句。
		 *
		 * \return 返回数据，失败返回NULL，返回的数据集使用YLR::YDataInterface::releaseDataTable方法释放。
		 */
		virtual const YDataTable * executeSqlReturnDt(const std::string & sql);

		/*!
		 * \brief
		 * 执行没有数据返回的sql语句。
		 * 作者：董帅 创建时间：2013-1-20 15:13:11
		 *
		 * \param sql 要执行的SQL语句。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool executeSqlWithOutDt(const std::string & sql);

	private:
		std::string * _filePath; /*!< 文件完整路径。 */ 
		std::string * _password; /*!< 文件登陆密码。 */

		DataBaseType _dataBaseType; /*!< 数据库类型。 */

		std::string * _errorText; /*!< 错误信息。 */

		_ConnectionPtr *_connection; /*!< ado数据库连接对象。 */
	};
}
}
#endif