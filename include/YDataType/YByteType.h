#ifndef V_BYTE_TYPE
#define V_BYTE_TYPE
// 此类是从 YByteType.dll 导出的

#ifdef YDATATYPE_EXPORTS
#	define YBYTETYPE_API __declspec(dllexport)
#else
#	define YBYTETYPE_API __declspec(dllimport)
#endif

#ifndef YBYTE
#define YBYTE unsigned char /*!< 自定义二进制数据类型 */
#endif

#include <stdio.h>
//#include <vector>
//#include <list>

namespace YLR
{
/*!
 * \brief
 * 二进制操作类，使用Win32项目创建DLL，在工程中引用。程序中所有代码均使用标准C++，方便今后项目移植。
 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 10:56
 */
class YBYTETYPE_API YByteType 
{
public:

	/*!
	 * \brief
	 * 构造函数，可以根据指定的数据初始化。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 11:00
	 *
	 * \param count 数据空间初始大小，默认值是0，表式暂不分配。
	 * \param initData 数据空间初始化缓冲区，默认值是NULL，表式无初始化数据。如果有初始化数据一定要保证数据的个数和count相等。
	 */
	YByteType(const unsigned int &count = 0, const YBYTE * initData = NULL);

	/*!
	 * \brief 拷贝构造函数
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 11:10
	 *
	 * \param item 要复制的数据对象
	 */
	YByteType(const YByteType &item);

	/*!
	 * \brief
	 * 析构函数，创建的数据空间在这里释放。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 11:20
	 */	 
	~YByteType();

	/*!
	 * \brief
	 * 设置数据空间，原数据存储空间中的数据也要做如下处理：
	 * 新空间小于等于原空间时，从新空间开始位置起，根据新空间的大小，将原有数据按顺序保存到新空间中，将超出新空间大小之外的数据舍弃。
	 * 新空间大于原空间时，从新空间起始位置开始，将原有数据按顺序保存到新空间中。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 11:30
	 *
	 * \param count 数据空间大小，默认值是0，表式清除数据。
	 *
	 * \return 如果设置大小成功则返回true，否则返回false。
	 */
	bool setSize(const unsigned int &count = 0);

	/*!
	 * \brief
	 * 获取数据空间大小。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 11:48
	 *
	 * \return 数据空间大小。
	 */
	unsigned int getSize() const;

	/*!
	 * \brief
	 * 设置单个数据，如果指定的位置超出范围，则放弃操作。设置结束后返回数据个数。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 13:35
	 *
	 * \param data 要设置的数据
	 * \param location 要设置的数据位置，默认是0。
	 *
	 * \return 设置的数据个数,这里应该返回1，否则设置失败。
	 */
	unsigned int setData(const YBYTE &data, const unsigned int &location = 0);

	/*!
	 * \brief
	 * 批量设置数据，如果超出范围超出部分舍弃。设置结束返回设置的数据个数。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 13:40
	 *
	 * \param data 要设置的数据数组首地址
	 * \param count 要设置的数据个数，默认值是0，此时使用'\0'标志结束。
	 * \param location 数据空间开始位置
	 *
	 * \return 设置的数据个数
	 */
	unsigned int setData(const YBYTE * data, const unsigned int &count, const unsigned int &location = 0);

	/*!
	 * \brief
	 * 获取数据。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 13:54
	 *
	 * \param data 要获取的数据返回值。
	 * \param location 数据空间的位置，如果指定位置超出范围则不进行任何操作。
	 *
	 * \return 返回获取的数据个数，这里应该返回1。
	 */
	unsigned int getData(YBYTE &data, const unsigned int &location = 0) const;

	/*!
	 * \brief
	 * 批量获取数据，如果获取的个数超出范围则舍弃超出部分。
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 13:59
	 *
	 * \param data 存储数据数组首地址
	 * \param count 获取数据个数，如果超出数据空间范围，超出部分舍弃。
	 * \param location 数据空间开始位置，默认是0
	 *
	 * \return 返回获取的数据个数。
	 */
	unsigned int getData(YBYTE * data, const unsigned int &count, const unsigned int &location = 0) const;

	/*!
	 * \brief
	 * 赋值操作符重载
	 * 版本：v0.1.0 作者：董帅 创建时间：2011-11-22 14:10
	 *
	 * \param item 要复制的原操作数
	 */
	YByteType & operator=(const YByteType &item);

protected:
	YBYTE * _data; /*!< 数据空间地址，初始值是NULL，表式还未分配。 */
	unsigned int _size; /*!< 数据存储空间大小，初始值是0，表式未分配空间。 */
};


//template class YBYTETYPE_API std::allocator<YByteType>;
//
//template class YBYTETYPE_API std::vector<YByteType,std::allocator<YByteType>>;
//
//template class YBYTETYPE_API std::allocator<std::_List_nod<YByteType,std::allocator<YByteType> >::_Node>;
//template class YBYTETYPE_API std::list<YByteType,std::allocator<YByteType>>;

};
#endif