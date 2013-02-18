#ifndef Y_MACHINE_INFO
#define Y_MACHINE_INFO

#include <string>

#include "../../YSystem/YSystem.h"

namespace YLR
{
/*!
 * \brief
 * 系统信息类库。
 */
namespace YSystem
{
	class YSYSTEM_API YMachineInfo
	{
	public:
		/*!
		 * \brief
		 * 获取CPU唯一标识。
		 * 作者：董帅 创建时间：2013-2-9 21:30:43
		 *
		 * \return CPU唯一标识，失败返回NULL，使用后用freeText方法释放。
		 */
		static std::string * getCpuID();

		/*!
		 * \brief
		 * 释放字符串。
		 * 作者：董帅 创建时间：2013-2-9 21:31:35
		 *
		 * \param s 要释放的字符串。
		 */
		static void freeText(std::string * s);
	};
}
}

#endif