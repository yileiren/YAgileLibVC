#ifndef Y_COLUMN
#define Y_COLUMN

#include "../../YDataBase/DLL_Config.h"
#include "../YDataType/YData.h"

#include <string>

namespace YLR
{
	/*!
	 * \brief
	 * 数据字段。
	 * 作者：董帅 创建时间：2012-11-5 21:49:49
	 */
	class YDATABASE_API YColumn 
	{
	public:
		/*!
		 * \brief
		 * 默认构造函数，初始化数据。
		 * 作者：董帅 创建时间：2012-11-5 21:53:34
		 */
		YColumn();

		/*!
		 * \brief
		 * 带有数据初始化的构造函数。
		 * 作者：董帅 创建时间：2012-11-5 22:02:19
		 *
		 * \param physicaName 物理名称
		 * \param logicalName 逻辑名称
		 * \param dataType 数据类型
		 */
		YColumn(const std::string & physicaName, const std::string & logicalName, const YData::DataType & dataType);

		/*!
		 * \brief
		 * 拷贝构造函数。
		 * 作者：董帅 创建时间：2012-11-5 22:06:05
		 *
		 * \param item 要拷贝的对象
		 */
		YColumn(const YColumn & item);
		
		/*!
		 * \brief
		 * 析构函数，释放对象所有资源。
		 * 作者：董帅 创建时间：2012-11-5 22:14:54
		 */
		~YColumn();

		/*!
		 * \brief
		 * 赋值操作符重载。
		 * 作者：董帅 创建时间：2012-11-5 22:14:54
		 *
		 * \param item 原数据对象。
		 * 
		 * \return 目标引用。
		 */
		YColumn & operator=(const YColumn & item);

		/*!
		 * \brief
		 * 设置字段物理名称。
		 * 作者：董帅 创建时间：2012-11-5 22:14:54
		 *
		 * \param physicaName 物理名称
		 */
		void setPhysicaName(const std::string & physicaName);

		/*!
		 * \brief
		 * 获取字段物理名称。
		 * 作者：董帅 创建时间：2012-11-5 22:17:31
		 *
		 * \return 字段物理名称指针const指针。
		 */
		const std::string * getPhysicaName() const;

		/*!
		 * \brief
		 * 设置字段逻辑名称。
		 * 作者：董帅 创建时间：2012-11-5 22:36:20
		 *
		 * \param logicalName 字段逻辑名称
		 */
		void setLogicalName(const std::string & logicalName);

		/*!
		 * \brief
		 * 获取字段逻辑名称。
		 * 作者：董帅 创建时间：2012-11-5 22:38:25
		 *
		 * \return 阻断逻辑名称const指针。
		 */
		const std::string * getLogicalName() const;	

		/*!
		 * \brief
		 * 设置数据类型。
		 * 作者：董帅 创建时间：2012-11-5 22:46:12
		 *
		 * \param dataType 数据类型。
		 */
		void setDataType(const YData::DataType & dataType);

		/*!
		 * \brief
		 * 获取字段数据类型。
		 * 作者：董帅 创建时间：2012-11-5 22:48:28
		 *
		 * \return 字段数据类型。
		 */
		const YData::DataType getDataType() const;

	protected:
		std::string * _physicaName; /*!<字段物理名称。 */
	
		std::string * _logicalName; /*!<字段逻辑名称。 */
    
		YData::DataType _dataType; /*!<字段数据类型。 */
	};
}
#endif 