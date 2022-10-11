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
			/// <param name="param">参考ReceiverParam</param>
			IMPReceiver(const ReceiverParam& param);

			/// <summary>
			/// 接收函数
			/// </summary>
			/// <param name="packet">数据包</param>
			/// <returns>成功返回true，错误返回false</returns>
			bool Read(Packet& packet) noexcept override;

			/// <summary>
			/// 关闭接收器
			/// </summary>
			/// <returns>成功返回true，错误返回false</returns>
			bool Close() noexcept override;
		private:
			/// <summary>传输类型</summary>
			NetType                           m_eType;
			/// <summary>本地端口</summary>
			uint16_t                          m_iPort;
			/// <summary>接收的最大长度</summary>
			size_t                            m_iMaxLength;
			/// 句柄
			std::unique_ptr<asio::io_context> m_pContext;
			/// <summary>UDPSocket</summary>
			std::unique_ptr<udp::socket>      m_pUdpSocket;
			/// <summary>TCPAcceptor</summary>
			std::unique_ptr<tcp::acceptor>    m_pAcceptor;
			
			
		};
		/// <summary>
		/// 发送器实现
		/// </summary>
		class TCPSender final : public Sender
		{
		public:
			/// <summary>
			/// 构造函数
			/// </summary>
			/// <param name="param">发送器参数</param>
			TCPSender(const SenderParam& __VSNC_IN param);

			/// <summary>
			/// 发送函数
			/// </summary>
			/// <param name="packet">数据包</param>
			/// <returns>成功返回true，错误返回false</returns>
			bool Send(const Packet& packet) noexcept override;

			/// <summary>
			/// 关闭发送器
			/// </summary>
			/// <returns>成功返回true，错误返回false</returns>
			bool Close() noexcept override;
		private:
			/// <summary>传输类型</summary>
			NetType                           m_eType;
			/// <summary>本地Address</summary>
			asio::ip::tcp::endpoint           m_pSrcEndpoint;
			/// <summary>目标Address</summary>
			asio::ip::tcp::endpoint           m_pDstEndpoint;
			/// <summary>接收的最大长度</summary>
			size_t                            m_iMaxLength;
			/// <summary>句柄</summary>
			std::unique_ptr<asio::io_context> m_pContext;
			/// <summary>TCPAcceptor</summary>
			std::unique_ptr<tcp::socket>      m_pSocket;
			/// <summary>Resolver</summary>
			std::unique_ptr<tcp::resolver>    m_pResolver;
			
		};
	}
}

#endif // !__HS_IMP_TRANSIMISSION_H__

