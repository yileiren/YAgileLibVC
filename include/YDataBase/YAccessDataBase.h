#ifndef Y_ACCESS_DATABASE
#define Y_ACCESS_DATABASE

#include "YDataInterface.h"
#include "ado\MSAdo.h"

namespace YLR
{
	class YDATABASE_API YAccessDataBase : public YDataInterface
	{
	public:
		/*!
		 * \brief
		 * 默认构造函数。
		 */
		YAccessDataBase();

		/*!
		 * \brief
		 * 拷贝构造函数。
		 */
		YAccessDataBase(const YAccessDataBase & item);

		/*!
		 * \brief
		 * 
		 */
		void setFilePath(const std::string & path);

	private:
		std::string * _filePath; /*!< 文件完整路径。 */ 
		std::string * _password; /*!< 文件登陆密码。 */
	};
}

#endif