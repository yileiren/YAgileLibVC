#ifndef Y_DATA_TABLE
#define Y_DATA_TABLE

#include <vector>

#include "../../YDataBase/DLL_Config.h"
#include "YDataRow.h"

namespace YLR
{
	/*!
	 * \brief
	 * 数据表类型封装。 
	 * 作者：董帅 创建时间：2012-12-18 16:12:12
	 */
	class YDATABASE_API YDataTable : public YDataColumns 
	{
	public:
		/*!
		 * \brief
		 * 构造函数。
		 * 作者：董帅 创建时间：2012-12-18 16:15:27
		 */
		YDataTable();

		/*!
		 * \brief
		 * 拷贝构造函数。
		 * 作者：董帅 创建时间：2012-12-18 16:19:00
		 */
		YDataTable(const YDataTable & item);

		/*!
		 * \brief
		 * 析构函数。
		 * 作者：董帅 创建时间：2012-12-18 16:21:10
		 */
		~YDataTable();

		/*!
		 * \brief
		 * 赋值操作符重载。
		 * 作者：董帅 创建时间：2012-12-18 16:23:26
		 */
		YDataTable & operator=(const YDataTable & item);

		/*!
		 * \brief
		 * 在数据列后面增加一列。
		 * 作者：董帅 创建时间：2012-12-18 16:25:13
		 *
		 * \param column 增加的列。
		 */
		virtual void addColumn(const YColumn & column);

		/** 
		 * \brief
		 * 在指定位置插入数据列。
		 * 作者：董帅 创建时间：2012-12-18 16:25:17
		 *
		 * \param index 插入位置，从0开始。
		 * \param column 插入的列。
		 */
		virtual void insertColumn(const int & index, const YColumn & column);

		/*!
		 * \brief
		 * 移除指定位置的数据列。
		 * 作者：董帅 创建时间：2012-12-18 16:25:22
		 *
		 * \param index 要移除的列索引位置，从0开始。
		 */
		virtual void removeColumn(const int & index);

		/*!
		 * \brief
		 * 获取指定位置的数据列，如果指定位置不存在返回NULL。
		 * 作者：董帅 创建时间：2012-12-18 16:25:26
		 *
		 * \param index 数据列索引，从0开始。
		 *
		 * \return 返回数据列指针。
		 */
		virtual const YColumn * getColumn(const int & index) const;

		/*!
		 * \brief
		 * 设置指定位置的数据列，如果指定位置不存在不做任何操作。
		 * 作者：董帅 创建时间：2012-12-18 16:25:29
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
		 * 在表末尾新增数据行。
		 * 作者：董帅 创建时间：2012-12-18 16:38:26
		 *
		 * \param row 数据行。
		 */
		void addRow(const YDataRow & row);

		/*!
		 * \brief
		 * 插入数据行。
		 * 作者：董帅 创建时间：2012-12-18 16:43:28
		 *
		 * \param index 索引位置。
		 */
		void insertRow(const int & index, const YDataRow & row);

		/*!
		 * \brief
		 * 移除指定的数据行。
		 * 作者：董帅 创建时间：2012-12-18 16:51:22
		 *
		 * \param index 索引位置。
		 */
		void removeRow(const int & index);

		/*!
		 * \brief
		 * 获取指定位置的数据行。
		 * 作者：董帅 创建时间：2012-12-18 16:54:22
		 *
		 * \param index 索引位置。
		 *
		 * \return 数据行指针，出错返回NULL。
		 */
		const YDataRow * getRow(const int & index) const;

		/*!
		 * \brief
		 * 设置数据行。
		 * 作者：董帅 创建时间：2012-12-18 16:57:20
		 *
		 * \param index 索引位置。
		 * \param row 数据行。
		 */
		void setRow(const int & index, const YDataRow & row);

		/*!
		 * \brief
		 * 获取数据行总数。
		 * 作者：董帅 创建时间：2012-12-18 17:31:18
		 *
		 * \return 行总数。
		 */
		int getRowCount() const;

		/*!
		 * \brief
		 * 获取指定位置的数据。
		 * 作者：董帅 创建时间：2012-12-18 16:59:39
		 *
		 * \param rowIndex 行索引值。
		 * \param columnIndex 列索引值。
		 * 
		 * \return 数据指针。
		 */
		const YData * getData(const int & rowIndex, const int & columnIndex) const;

		/*!
		 * \brief
		 * 获取指定位置的数据。
		 * 作者：董帅 创建时间：2012-12-18 17:07:36
		 *
		 * \param rowIndex 行索引值。
		 * \param physicaName 列逻辑名称。
		 * 
		 * \return 数据指针。
		 */
		const YData * getData(const int & rowIndex, const std::string & physicaName) const;

		/*!
		 * \brief
		 * 获取指定位置的数据。
		 * 作者：董帅 创建时间：2012-12-18 17:07:36
		 *
		 * \param rowIndex 行索引值。
		 * \param columnIndex 列索引值。
		 * \param data 数据。
		 */
		void setData(const int & rowIndex, const int & columnIndex, const YData & data);

		/*!
		 * \brief
		 * 获取指定位置的数据。
		 * 作者：董帅 创建时间：2012-12-18 17:13:52
		 *
		 * \param rowIndex 行索引值。
		 * \param physicaName 列逻辑名称。
		 * \param data 数据。
		 */
		void setData(const int & rowIndex, const std::string & physicaName, const YData & data);
	protected:
		std::vector<YColumn> * _columns; /*!< 数据列。 */
		std::vector<YDataRow> * _rows; /*!< 数据行。 */
	};
}

#endif