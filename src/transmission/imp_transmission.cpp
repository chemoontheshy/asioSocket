#include "imp_transmission.h"


hs::net::IMPReceiver::IMPReceiver(const ReceiverParam& param):
	m_eType(param.Type),m_iPort(param.Port),m_iMaxLength(param.MaxLength),
	m_pContext(std::make_unique<asio::io_context>())
{

	try
	{
		switch (m_eType)
		{
		case hs::net::NetType::TCP:
		{
			m_pAcceptor = std::make_unique<tcp::acceptor>(*m_pContext, tcp::endpoint(tcp::v4(), static_cast<asio::ip::port_type>(m_iPort)));
		}
		case hs::net::NetType::UDP:
		{
			m_pUdpSocket = std::make_unique<udp::socket>(*m_pContext, udp::endpoint(udp::v4(), static_cast<asio::ip::port_type>(m_iPort)));
			asio::ip::udp::socket::send_buffer_size sbs(10240);
			m_pUdpSocket->set_option(sbs);

		}
		default:
			break;
		}
	}
	catch(...)
	{
		std::cout <<"create socket ip:127.0.0.1:"+std::to_string(m_iPort)+" failed!!!" << std::endl;
	}
	
}

bool hs::net::IMPReceiver::Read(Packet& packet) noexcept
{

	bool flag = false;
	udp::endpoint sender_endpoint;
	switch (m_eType)
	{
	case hs::net::NetType::TCP:
	{
		asio::error_code error;
		auto length = m_pAcceptor->accept().read_some(asio::buffer(packet.Data, m_iMaxLength), error);
		if (length != 0 && length < m_iMaxLength)
		{

			packet.Length = length;
			flag = true;
		}
		break;
	}
	case hs::net::NetType::UDP:
	{
		udp::endpoint senderPonit;
		auto length = m_pUdpSocket->receive_from(asio::buffer(packet.Data, m_iMaxLength), senderPonit);
		
		if (length != 0 && length < m_iMaxLength)
		{

			packet.Length = length;
			flag = true;
		}
		break;
	}
	default:
		break;
	}
	return flag;
}
