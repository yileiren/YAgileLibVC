#ifndef Y_DATA_INTERFACE
#define Y_DATA_INTERFACE

#include <string>

#include "../../YDataBase/DLL_Config.h"
#include "YDataTable.h"

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
	 * 数据库连接接口，定义所有数据库连接的标准方法。
	 * 作者：董帅 创建时间：2013-1-7 15:58:09
	 */
	class YDATABASE_API YDataInterface
	{
	public:

		/*!
		 * \brief
		 * 数据库连接状态枚举值。
		 * 作者：董帅 创建时间：2013-1-7 16:02:17。
		 */
		enum ConnectState
		{
			Connected,          /*!< 已经连接。 */
			Disconnected        /*!< 连接断开。 */
		};

		/*!
		 * \brief
		 * 数据库类型。
		 * 作者：董帅 创建时间：2013-1-7 16:04:05
		 */
		enum DataBaseType
		{
			MSSQL,            /*!< 微软SqlServer数据库。 */
			Access,           /*!< 微软Access数据库。 */
			SQLite            /*!< SQLite数据库。 */
		};

		/*!
		 * \brief
		 * 获取数据库类型。
		 * 作者：董帅 创建时间：2013-1-7 15:58:46
		 *
		 * \return 数据库类型。
		 */
		virtual DataBaseType databaseType()  = 0;

		/*!
		 * \brief
		 * 获取上次操作的错误信息。
		 * 作者：董帅 创建时间：2013-1-7 15:59:23
		 *
		 * \return 错误信息。
		 */
		virtual const std::string * errorMessage()  = 0;

		/*!
		 * \brief
		 * 连接数据库。
		 * 作者：董帅 创建时间：2013-1-7 16:00:35
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool connectDataBase()  = 0;

		/*!
		 * \brief
		 * 断开数据库连接。
		 * 作者：董帅 创建时间：2013-1-7 16:06:04
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool disconnectDataBase()  = 0;

		/*!
		 * \brief
		 * 获取连接状态。
		 * 作者：董帅 创建时间：2013-1-7 16:06:51
		 *
		 * \return 连接转台。
		 */
		virtual ConnectState connectState()  = 0;

		/*!
		 * \brief
		 * 开启数据库事务。
		 * 作者：董帅 创建时间：2013-1-7 16:07:56
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool beginTransaction()  = 0;

		/*!
		 * \brief
		 * 提交事务。
		 * 作者：董帅 创建时间：2013-1-7 16:08:59
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool commitTransaction()  = 0;

		/*!
		 * \brief
		 * 回滚事务。
		 * 作者：董帅 创建时间：2013-1-7 16:09:40
		 *
		 * \return 成功返回true，否则返回false。
		 */
		virtual bool rollbackTransaction()  = 0;

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

		/*!
		 * \brief
		 * 释放数据集。
		 * 作者：董帅 创建时间：2013-1-16 17:40:35
		 *
		 * \param t 要释放的数据集。
		 */
		static void releaseDataTable(const YDataTable *t)
		{
			delete t;
		}
	};
}
}
#endif