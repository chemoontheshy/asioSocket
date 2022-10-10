#ifndef __HS_TRANSMISSION_H__
#define __HS_TRANSMISSION_H__

#include "utils/vsnc_utils.h"


using vsnc::stucture::Packet;

namespace hs
{
	namespace net
	{
		
		/// <summary>
		/// 传输类型
		/// </summary>
		enum class NetType
		{
			// TCP
			TCP,
			// UDP
			UDP
		};

		/// <summary>
		/// 接收器
		/// </summary>
		class Receiver
		{
		public:
			/// <summary>
			/// 接收器
			/// </summary>
			virtual ~Receiver() = default;
			
			/// <summary>
			/// 接收函数
			/// </summary>
			/// <param name="packet">数据包</param>
			/// <returns>成功返回true，错误返回false</returns>
			virtual bool Read(Packet& __VSNC_IN_OUT packet) noexcept = 0;
		};
		class Sender
		{
		public:
			/// <summary>
			/// 析构函数
			/// </summary>
			virtual ~Sender() = default;

			/// <summary>
			/// 发送器
			/// </summary>
			/// <param name="packet">数据包</param>
			/// <returns>成功返回true，错误返回false</returns>
			virtual bool Send(const Packet& __VSNC_IN packet) noexcept = 0;
		};

		/// <summary>
		/// 创建接收器参数
		/// </summary>
		struct ReceiverParam
		{

			/// 传输类型
			NetType  Type;
			/// 本地端口
			uint16_t Port;
			/// 接收最大长度
			size_t   MaxLength;
		};

		std::shared_ptr<Receiver> CreateReceiver(const ReceiverParam& __VSNC_IN param);

		/// <summary>
		/// 发送器参数
		/// </summary>
		struct SenderParam
		{
			/// 传输类型
			NetType     Type;
			/// 本地端口 :为0时由系统分配，不为0则可指定
			uint16_t    Port;
			/// 目标IP
			std::string DstIP;
			/// 目标Port
			uint16_t    DstPort;
			/// 发送最大长度
			size_t      MaxLength;
		};
	}
}

#endif // !__HS_TRANSMISSION_H__

