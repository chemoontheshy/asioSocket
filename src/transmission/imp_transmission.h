#ifndef __HS_IMP_TRANSIMISSION_H__
#define __HS_IMP_TRANSIMISSION_H__

#include "transmission.h"
#include "asio/asio.hpp"

using asio::ip::udp;
using asio::ip::tcp;

namespace hs
{
	namespace net
	{
		/// <summary>
		/// 接收器实现
		/// </summary>
		class IMPReceiver final : public Receiver
		{
		public:
			/// <summary>
			/// 构造函数
			/// </summary>
			/// <param name="param"></param>
			IMPReceiver(const ReceiverParam& param);

			/// <summary>
			/// 接收函数
			/// </summary>
			/// <param name="packet">数据包</param>
			/// <returns>成功返回true，错误返回false</returns>
			bool Read(Packet& packet) noexcept override;
		private:
			/// 传输类型
			NetType                           m_eType;
			/// 本地端口
			uint16_t                          m_iPort;
			/// 接收最大长度
			size_t                            m_iMaxLength;
			/// 句柄
			std::unique_ptr<asio::io_context> m_pContext;
			/// UDPSocket
			std::unique_ptr<udp::socket>      m_pUdpSocket;
			/// TCPSocket
			std::unique_ptr<tcp::acceptor>    m_pAcceptor;
		};
	}
}

#endif // !__HS_IMP_TRANSIMISSION_H__

