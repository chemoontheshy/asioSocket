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
		/// ������ʵ��
		/// </summary>
		class IMPReceiver final : public Receiver
		{
		public:
			/// <summary>
			/// ���캯��
			/// </summary>
			/// <param name="param">�ο�ReceiverParam</param>
			IMPReceiver(const ReceiverParam& param);

			/// <summary>
			/// ���պ���
			/// </summary>
			/// <param name="packet">���ݰ�</param>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			bool Read(Packet& packet) noexcept override;

			/// <summary>
			/// �رս�����
			/// </summary>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			bool Close() noexcept override;
		private:
			/// <summary>��������</summary>
			NetType                           m_eType;
			/// <summary>���ض˿�</summary>
			uint16_t                          m_iPort;
			/// <summary>���յ���󳤶�</summary>
			size_t                            m_iMaxLength;
			/// ���
			std::unique_ptr<asio::io_context> m_pContext;
			/// <summary>UDPSocket</summary>
			std::unique_ptr<udp::socket>      m_pUdpSocket;
			/// <summary>TCPAcceptor</summary>
			std::unique_ptr<tcp::acceptor>    m_pAcceptor;
			
			
		};
		/// <summary>
		/// ������ʵ��
		/// </summary>
		class TCPSender final : public Sender
		{
		public:
			/// <summary>
			/// ���캯��
			/// </summary>
			/// <param name="param">����������</param>
			TCPSender(const SenderParam& __VSNC_IN param);

			/// <summary>
			/// ���ͺ���
			/// </summary>
			/// <param name="packet">���ݰ�</param>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			bool Send(const Packet& packet) noexcept override;

			/// <summary>
			/// �رշ�����
			/// </summary>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			bool Close() noexcept override;
		private:
			/// <summary>��������</summary>
			NetType                           m_eType;
			/// <summary>����Address</summary>
			asio::ip::tcp::endpoint           m_pSrcEndpoint;
			/// <summary>Ŀ��Address</summary>
			asio::ip::tcp::endpoint           m_pDstEndpoint;
			/// <summary>���յ���󳤶�</summary>
			size_t                            m_iMaxLength;
			/// <summary>���</summary>
			std::unique_ptr<asio::io_context> m_pContext;
			/// <summary>TCPAcceptor</summary>
			std::unique_ptr<tcp::socket>      m_pSocket;
			/// <summary>Resolver</summary>
			std::unique_ptr<tcp::resolver>    m_pResolver;
			
		};
	}
}

#endif // !__HS_IMP_TRANSIMISSION_H__

