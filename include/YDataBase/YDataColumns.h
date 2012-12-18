#ifndef Y_DATA_COLUMNS
#define Y_DATA_COLUMNS

#include "../../YDataBase/DLL_Config.h"
#include "YColumn.h"

namespace YLR 
{
/** 
 * \brief
 * 数据表字段接口定义。
 * 作者：董帅 创建时间：2012-11-26 21:11:19
 */
class YDATABASE_API YDataColumns {

 public:


    /*! 
     * \brief
	 * 在数据列后面增加一列。
	 * 作者：董帅 创建时间：2012-11-26 21:11:55
	 *
	 * \param column 增加的列。
     */
    virtual void addColumn(const YColumn & column) = 0;


    /*!
     * \brief
	 * 在指定位置插入数据列。
	 * 作者：董帅 创建时间：2012-11-26 21:16:13
	 *
	 * \param index 插入位置，从0开始。
	 * \param column 插入的列。
     */
    virtual void insertColumn(const int & index, const YColumn & column) = 0;


    /*!
     * \brief
	 * 移除指定位置的数据列。
	 * 作者：董帅 创建时间：2012-11-26 21:17:16
	 *
	 * \param index 要移除的列索引位置，从0开始。
     */
    virtual void removeColumn(const int & index) = 0;

	/*!
	 * \brief
	 * 获取指定位置的数据列，如果指定位置不存在返回NULL。
	 * 作者：董帅 创建时间：2012-12-18 12:41:18
	 *
	 * \param index 数据列索引，从0开始。
	 *
	 * \return 返回数据列指针。
	 */
	virtual const YColumn * getColumn(const int & index) const = 0;

	/*!
	 * \brief
	 * 设置指定位置的数据列，如果指定位置不存在不做任何操作。
	 * 作者：董帅 创建时间：2012-12-18 12:45:33
	 *
	 * \param index 索引位置，从0开始。
	 * \param column 数据列。
	 */
	virtual void setColumn(const int & index, const YColumn & column) = 0;

	/*!
	 * \brief
	 * 获取数据列总数。
	 * 作者：董帅 创建时间：2012-12-18 17:28:10
	 *
	 * \return 列总数。
	 */
	virtual int getColumnCount() const  = 0;
};

}

#endif