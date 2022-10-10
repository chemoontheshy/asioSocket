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
			/// <param name="param"></param>
			IMPReceiver(const ReceiverParam& param);

			/// <summary>
			/// ���պ���
			/// </summary>
			/// <param name="packet">���ݰ�</param>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			bool Read(Packet& packet) noexcept override;
		private:
			/// ��������
			NetType                           m_eType;
			/// ���ض˿�
			uint16_t                          m_iPort;
			/// ������󳤶�
			size_t                            m_iMaxLength;
			/// ���
			std::unique_ptr<asio::io_context> m_pContext;
			/// UDPSocket
			std::unique_ptr<udp::socket>      m_pUdpSocket;
			/// TCPSocket
			std::unique_ptr<tcp::acceptor>    m_pAcceptor;
		};
	}
}

#endif // !__HS_IMP_TRANSIMISSION_H__

