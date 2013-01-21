#ifndef Y_TEXT_ENCODE
#define Y_TEXT_ENCODE

#include <string>

#include "YDataTypeConfig.h"

namespace YLR
{
	/*!
	 * \brief
	 * 编码集转换处理类。
	 * 作者：董帅 创建时间：2013-1-21 17:47:08
	 */
	class YBYTETYPE_API YTextEncode
	{
	public:
		/*!
		 * \brief
		 * 释放文本空间。
		 * 作者：董帅 创建时间：2013-1-21 17:46:37
		 *
		 * \param text 文本指针。
		 */
		static void freeText(std::string * text);

		/*!
		 * \brief
		 * 释放文本空间。
		 * 作者：董帅 创建时间：2013-1-21 17:46:37
		 *
		 * \param text 文本指针。
		 */
		static void freeText(std::wstring * text);

		/*!
		 * \brief
		 * 将utf8转换成unicode。
		 * 作者：董帅 创建时间：2013-1-21 17:48:32
		 *
		 * \param text 要转换的文本。
		 *
		 * \return 转换后的文本，出错返回NULL，用完使用freeText方法释放。
		 */
		static std::wstring * utf8ToUnicode(const std::string & text);
	};
}

#endif