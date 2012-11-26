#ifndef Y_DATA_COLUMNS
#define Y_DATA_COLUMNS

#include "../include/YDataBase/YColumn.h"

namespace YLR 
{
/** 
 * \brief
 * 数据表字段接口定义。
 * 作者：董帅 创建时间：2012-11-26 21:11:19
 */
class YDataColumns {

 public:


    /** 
     * \brief
	 * 在数据列后面增加一列。
	 * 作者：董帅 创建时间：2012-11-26 21:11:55
	 *
	 * \param column 增加的列。
     */
    virtual void addColumn(const YColumn & column)  = 0;


    /** 
     * \brief
	 * 在指定位置插入数据列。
	 * 作者：董帅 创建时间：2012-11-26 21:16:13
	 *
	 * \param index 插入位置，从0开始。
	 * \param column 插入的列。
     */
    virtual void insertColumn(const int & index, const YColumn & column)  = 0;


    /** 
     * \brief
	 * 移除指定位置的数据列。
	 * 作者：董帅 创建时间：2012-11-26 21:17:16
	 *
	 * \param index 要移除的列索引位置，从0开始。
     */
    virtual void removeColumn(const int & index)  = 0;
};

}

#endif