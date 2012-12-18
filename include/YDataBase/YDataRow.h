#ifndef Y_DATA_ROW
#define Y_DATA_ROW

#include <vector>

#include "../../YDataBase/DLL_Config.h"
#include "YDataColumns.h"

namespace YLR
{
	/*!
	 * \brief
	 * 数据行类型封装。
	 * 作者：董帅 创建时间：2012-12-10 19:58:12
	 */
	class YDATABASE_API YDataRow : public YDataColumns 
	{
	public:
		/*!
		 * \brief
		 * 默认构造函数。
		 * 作者：董帅 创建时间：2012-12-10 20:05:21
		 */
		YDataRow();

		/*!
		 * \brief
		 * 拷贝构造函数。
		 * 作者：董帅 创建时间：2012-12-12 21:26:09
		 */
		YDataRow(const YDataRow & item);

		/*!
		 * \brief
		 * 析构函数。
		 */
		~YDataRow();

		/*!
		 * \brief
		 * 赋值操作符重载。
		 * 作者：董帅 创建时间：2012-12-12 21:37:50
		 */
		YDataRow & operator=(const YDataRow & item);

		/*!
		 * \brief
		 * 在数据列后面增加一列。
		 * 作者：董帅 创建时间：2012-12-12 21:42:22
		 *
		 * \param column 增加的列。
		 */
		virtual void addColumn(const YColumn & column);

		/** 
		 * \brief
		 * 在指定位置插入数据列。
		 * 作者：董帅 创建时间：2012-12-12 22:13:23
		 *
		 * \param index 插入位置，从0开始。
		 * \param column 插入的列。
		 */
		virtual void insertColumn(const int & index, const YColumn & column);

		/*!
		 * \brief
		 * 移除指定位置的数据列。
		 * 作者：董帅 创建时间：2012-12-12 22:13:27
		 *
		 * \param index 要移除的列索引位置，从0开始。
		 */
		virtual void removeColumn(const int & index);

		/*!
		 * \brief
		 * 获取指定位置的数据列，如果指定位置不存在返回NULL。
		 * 作者：董帅 创建时间：2012-12-18 12:41:18
		 *
		 * \param index 数据列索引，从0开始。
		 *
		 * \return 返回数据列指针。
		 */
		virtual const YColumn * getColumn(const int & index) const;

		/*!
		 * \brief
		 * 设置指定位置的数据列，如果指定位置不存在不做任何操作。
		 * 作者：董帅 创建时间：2012-12-18 12:45:33
		 *
		 * \param index 索引位置，从0开始。
		 * \param column 数据列。
		 */
		virtual void setColumn(const int & index, const YColumn & column);

		/*!
		 * \brief
		 * 获取数据列总数。
		 * 作者：董帅 创建时间：2012-12-18 17:28:10
		 *
		 * \return 列总数。
		 */
		virtual int getColumnCount() const;

		/*!
		 * \brief
		 * 获取数据。
		 * 作者：董帅 创建四件：2012-12-12 22:22:50
		 *
		 * \param index 索引值。
		 *
		 * \return 数据指针，失败返回NULL。
		 */
		const YData * getData(const int & index) const;

		/*!
		 * \brief
		 * 获取数据。
		 * 作者：董帅 创建时间：2012-12-18 12:54:51
		 *
		 * \param physicaName 字段逻辑名称。
		 *
		 * \return 数据指针，失败返回NULL。
		 */
		const YData * getData(const std::string & physicaName) const;

		/*!
		 * \brief
		 * 设置数据。
		 * 作者：董帅 创建时间：2012-12-18 13:04:31
		 * 
		 * \param index 索引位置，从0开始。
		 * \param data 数据。
		 */
		void setData(const int & index, const YData & data);

		/*!
		 * \brief
		 * 设置数据。
		 * 作者：董帅 创建时间：2012-12-18 13:10:26
		 * 
		 * \param physicaName 逻辑名称。
		 * \param data 数据。
		 */
		void setData(const std::string & physicaName, const YData & data);
	protected:
		std::vector<YColumn> * _columns; /*!< 列字段列表。 */
    
		std::vector<YData> * _datas; /*!< 数据列表。 */
	};
};

#endif