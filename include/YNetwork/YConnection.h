#ifndef Y_CONNECTION
#define Y_CONNECTION

#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "../../YNetwork/YNetwork.h"

#include "../YDataType/YByteType.h"

/*!
 * \brief
 * 异类人VC敏捷开发库。
 */
namespace YLR
{

/*!
 * \brief
 * 网络操作类库。
 */
namespace YNetWork
{
	/*!
	 * \brief
	 * 网络连接处理类，用来处理连接状态和数据传输。
	 * 数据传输过程中数据包格式为：
	 * 数据包字段说明:     |状态字|数据包总个数|当前数据包序号|数据包中数据长度|数据|结束|
	 * 各个字段长度(字节): | 1    |   4       |     4       |     4         | x  | 1 |
	 * 
	 * 详细说明：
	 * 状态字：标识该数据包的类型，状态字类型为StatusWord中的。
	 * 数据包总个数：本次发送的数据被分成的数据包总数，无符号整形。
	 * 当前数据包序号：本次发送的数据包在总个数中的序号，无符号整形。
	 * 数据包中数据长度：本数据包中的数据长度，无符号整形。
	 * 数据：数据包中的数据，长度为数据包中数据长度约定的长度。
	 * 结束：使用空字符（'\0'）做为结束标识。
	 *
	 * 作者：董帅 创建时间：2013-2-17 14:43:41
	 */
	class YNETWORK_API YConnection
	{
	public:
		enum StatusWord
		{
			EndFlag = 0x00,        /*!< 数据包结束位。 */

			Yes = 0x01,            /*!< 请求成功。 */
			No = 0x02,             /*!< 请求失败。 */
			Go = 0x03,             /*!< 继续。 */
			End = 0x04,            /*!< 结束。 */
			Error = 0x05,          /*!< 出错。 */

			Connect = 0x11,        /*!< 请求连接。 */
			Disconnect = 0x12,     /*!< 请求断开连接。 */

			SendData = 0x21,       /*!< 请求发送数据。 */

			DataPackage = 0xFF     /*!< 数据包，不含有状态。 */
		};

		/*!
		 * \brief
		 * 默认构造函数。
		 * 作者：董帅 创建时间：2013-2-17 14:45:27
		 */
		YConnection();

		/*!
		 * \brief
		 * 设置套接字接收超时时间。
		 * 作者：董帅 创建时间：2013-2-18 13:07:40
		 *
		 * \param s 要设置的套接字。
		 * \param t 超时时间，单位（毫秒）。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		bool setRcvTimeOut(SOCKET s,const int &t);

		/*!
		 * \brief
		 * 获取套接字接收超时时间。
		 * 作者：董帅 创建时间：2013-2-18 13:16:52
		 *
		 * \param s 要获取的套接字。
		 *
		 * \return 超时时间，单位（毫秒），失败返回-1。
		 */
		int getRcvTimeOut(SOCKET s);

		/*!
		 * \brief
		 * 设置发送超时时间。
		 * 作者：董帅 创建时间：2013-2-18 14:33:37
		 *
		 * \param s 要设置的套接字。
		 * \param t 超时时间，单位（毫秒）。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		bool setSndTimeOut(SOCKET s,const int &t);

		/*!
		 * \brief
		 * 获取套接字发送超时时间。
		 * 作者：董帅 创建时间：2013-2-18 14:45:46
		 *
		 * \param s 要获取的套接字。
		 *
		 * \return 超时时间，单位（毫秒），失败返回-1。
		 */
		int getSndTimeOut(SOCKET s);

		/*!
		 * \brief
		 * 发送数据。
		 * 作者：董帅 创建时间：2013-2-18 14:56:57
		 *
		 * \param s 使用的套接字。
		 * \param data 要发送的数据。
		 * \param packageCount 每一次发送的数据长度（如果数据较长需要拆成若干个包发送，只需要设置每个包的长度即可），单位是字节。
		 * \param sendTimeOut 每个包的发送超时时间。
		 * \param rcvTimeOut 每个包的接收超时时间。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		bool sendData(SOCKET s,const YDataType::YByteType &data,const int &packageCount,const int &sndTimeOut,const int &rcvTimeOut);

		/*!
		 * \brief
		 * 接收数据。
		 * 作者：董帅 创建时间：2013-2-19 11:26:06
		 *
		 * \param s 使用的套接字。
		 * \param data 接收到得数据。
		 * \param bufLength 接收数据缓冲区大小。
		 * \param sendTimeOut 每个包的发送超时时间。
		 * \param rcvTimeOut 每个包的接收超时时间。
		 *
		 * \return 成功返回true，否则返回false。
		 */
		bool recaiveData(SOCKET s,YDataType::YByteType &data,const int &bufLength,const int &sndTimeOut,const int &rcvTimeOut);
	};
}
}

#endif