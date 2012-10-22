#ifndef Y_DATA
#define Y_DATA

#include <string>

#include "YDataTypeConfig.h"
#include "YByteType.h"

namespace YLR
{
	/*!
	 * \brief
	 * 自定义通用数据类型，用于常用数据类型数据的保存和相互转换。
	 * 作者：董帅 创建时间：2012-4-22 15:00:49
	 * 版本号：v0.1.0
	 * 主要功能：
	 * 完成int、double、float、string类型的保存和相互转换。
	 */
	class YBYTETYPE_API YData : public YByteType
	{
	public:

		/*!
		 * \brief
		 * 自定义数据类型种类。
		 */
		enum DatyType
		{
			YInt,         /*!< int类型 */
			YDouble,      /*!< double类型 */
			YFloat,       /*!< float类型 */
			YString       /*!< string类型 */
		};

		/*!
		 * \brief
		 * 默认构造函数，数据初始化成NULL，数据类型设置成YInt。
		 * 作者：董帅 创建时间：2012-4-22 15:03:24
		 */
		YData();

		/*!
		 * \brief
		 * 使用int类型的数据初始化的构造函数。
		 * 作者：董帅 创建时间：2012-4-22 15:11:12
		 *
		 * \param d 初始化的数据。
		 */
		YData(const int &d);

 		/*!
		 * \brief
		 * 使用double类型的数据初始化的构造函数。
		 * 作者：董帅 创建时间：2012-4-22 15:34:16
		 *
		 * \param d 初始化的数据。
		 */
		YData(const double &d);

		/*!
		 * \brief
		 * 使用float类型的数据初始化的构造函数。
		 * 作者：董帅 创建时间：2012-4-22 15:38:16
		 *
		 * \param d 初始化的数据。
		 */
		YData(const float &d);

		/*!
		 * \brief
		 * 使用string类型的数据初始化的构造函数。
		 * 作者：董帅 创建时间：2012-4-22 15:45:46
		 *
		 * \param d 初始化的数据。
		 */
		YData(const std::string &d);

		/*!
		 * \brief
		 * 拷贝构造函数。
		 * 作者：董帅 创建时间：2012-4-24 21:57:04
		 */
		YData(const YData &item);

		/*!
		 * \brief
		 * 析构函数，释放空间。
		 * 作者：董帅 创建时间：2012-4-24 20:42:40
		 */
		~YData();

		/*!
		 * \brief
		 * 获取数据类型。
		 * 作者：董帅 创建时间：2012-4-22 17:23:45
		 *
		 * \return 数据类型。
		 */
		YData::DatyType getDataType() const;

		/*!
		 * \brief
		 * 将数据设置成NULL。
		 * 作者：董帅 创建时间：2012-4-22 15:59:51
		 */
		void setNull();

		/*!
		 * \brief
		 * 判断数据是否是NULL。
		 * 作者：董帅 创建时间：2012-10-22 21:27:32
		 *
		 * \return 是NULL返回true，否则返回false。
		 */
		bool isNull() const;

		/*!
		 * \brief
		 * 设置数据。
		 * 作者：董帅 创建时间：2012-4-22 16:41:16
		 *
		 * \param d 数据
		 */
		void setFrom(const int &d);

		/*!
		 * \brief
		 * 设置数据。
		 * 作者：董帅 创建时间：2012-4-22 16:41:29
		 *
		 * \param d 数据
		 */
		void setFrom(const double &d);

		/*!
		 * \brief
		 * 设置数据。
		 * 作者：董帅 创建时间：2012-4-22 16:41:29
		 *
		 * \param d 数据
		 */
		void setFrom(const float &d);

		/*!
		 * \brief
		 * 设置数据。
		 * 作者：董帅 创建时间：2012-4-22 16:41:29
		 *
		 * \param d 数据
		 */
		void setFrom(const std::string &d);

		/*!
		 * \brief
		 * 转换成int类型，方法根据数据类型自动转换，注意判断原数据类型与目的类型是
		 * 否兼容，特别注意NULL类型。
		 * 作者：董帅 创建时间：2012-4-22 16:50:30
		 *
		 * \return 转换后的数据。
		 */
		int toInt() const;

		/*!
		 * \brief
		 * 转换成double类型，方法根据数据类型自动转换，注意判断原数据类型与目的类型是
		 * 否兼容，特别注意NULL类型。
		 * 作者：董帅 创建时间：2012-4-22 21:09:15
		 *
		 * \return 转换后的数据。
		 */
		double toDouble() const;

		/*!
		 * \brief
		 * 转换成float类型，方法根据数据类型自动转换，注意判断原数据类型与目的类型是
		 * 否兼容，特别注意NULL类型。
		 * 作者：董帅 创建时间：2012-4-22 21:13:37
		 *
		 * \return 转换后的数据。
		 */
		float toFloat() const;

		/*!
		 * \brief
		 * 转换成string类型指针，对象销毁时空间释放，方法根据数据类型自动转换，注意判断原数据类型与目的类型是
		 * 否兼容，特别注意NULL类型。
		 * 作者：董帅 创建时间：2012-4-22 21:18:00
		 *
		 * \return 转换后的数据。
		 */
		std::string * toString();

		/*!
		 * \brief
		 * 负值操作符重载。
		 * 作者：董帅 创建时间：2012-4-24 22:13:44
		 */
		YData & operator=(const YData &item);
	protected:
		YData::DatyType _type; /*!< 数据类型 */

		std::string * str; /*!< 返回的字符串 */
	};
};

#endif