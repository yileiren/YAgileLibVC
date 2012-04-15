#ifndef V_SERIAL_PORT
#define V_SERIAL_PORT

#ifdef YSERIALPORT_EXPORTS
#define YSERIALPORTCE_API __declspec(dllexport)
#else
#define YSERIALPORTCE_API __declspec(dllimport)
#endif

#include <windows.h>

namespace YLR
{


	/*!
	 * \brief 
	 * 串口通信类，默认的串口参数为：
	 * 串口号：COM1
	 * 波特率：9600
	 * 校验位：NONE
	 * 数据位：8
	 * 停止位：1
	 *
	 * 创建时间：2011-06-08 9:00:00 创建人：董帅
	 * 版本号：V0.1.0
	 *
	 * 将原来的MFC工程修改成Win32动态库。
	 * 版本号：v0.2.0 作者：董帅 创建时间：2012-1-12 16:45:44
	*/
	class YSERIALPORTCE_API YSerialPort
	{
	public:
		/*!
		\brief 默认构造函数
		*/
		YSerialPort(void);
		~YSerialPort(void);

		/*!
		\brief 校验位类型
		*/
		enum Parity
		{
			NoParity = NOPARITY,
			ODDParity = ODDPARITY,
			EvenParity = EVENPARITY,
	 		MarkParity = MARKPARITY,
			SpaceParity = SPACEPARITY
		};

		/*!
		\brief 停止位类型
		*/
		enum StopBits
		{
			OneStopBit = ONESTOPBIT,
			One5StopBits = ONE5STOPBITS,
			TwoStopBits = TWOSTOPBITS
		};

		int serialNum; /*!< 串口号 */

		int baudRate; /*!< 波特率 */

		int byteSize; /*!< 数据位 */

		Parity parity; /*!< 校验位 */

		StopBits stopBits; /*!< 停止位 */

	private:
		HANDLE serialPort; /*!< 串口句柄 */
	public:
		/*!
		\brief 打开串口

		\return 成功返回true，否则返回false
		\sa bool closeSerialPort(void)
		*/
		bool openSerialPort(void);

		/*!
		\brief 关闭串口

		\return 成功返回true，否则返回false
		\sa bool openSerialPort(void)
		*/
		bool closeSerialPort(void);
		
		/*!
		\brief 发送数据

		\param data 发送数据缓冲区地址
		\param count 发送的数量

		\return 成功返回发送的字节数，返回-1表式串口未打开，返回-2表式发送失败，
				-3表式清空发送缓冲区失败，-4表式清空接收缓冲区失败
		\sa int receiveDate(unsigned char * data, const int & count)
		*/
		int sendData(const unsigned char * data, const int & count);
		
		/*!
		\brief 接收数据

		\param data 接收数据缓冲区地址
		\param count 接收数量

		\return 成功返回接收的字节数，返回-1表式串口未打开，返回-2表式接收失败
		\sa int sendData(const unsigned char * data, const int & count);
		*/
		int receiveDate(unsigned char * data, const int & count);
	};
};
#endif