#include "imp_transmission.h"

namespace hs
{
	namespace net
	{
		/// <summary>socket»º´æÇø</summary>
		constexpr size_t BUFFER_SIZE = 10240;
	}
}

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
			asio::socket_base::receive_buffer_size sbs(BUFFER_SIZE);
			m_pAcceptor->set_option(sbs);
		}
		case hs::net::NetType::UDP:
		{
			m_pUdpSocket = std::make_unique<udp::socket>(*m_pContext, udp::endpoint(udp::v4(), static_cast<asio::ip::port_type>(m_iPort)));
			asio::socket_base::receive_buffer_size sbs(BUFFER_SIZE);
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
		
		if (length >0)
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

bool hs::net::IMPReceiver::Close() noexcept
{
	if (!m_pUdpSocket) m_pUdpSocket->close();
	if (!m_pAcceptor) m_pAcceptor->close();
	return false;
}

hs::net::TCPSender::TCPSender(const SenderParam& __VSNC_IN param):
	m_eType(param.Type),
	m_pSrcEndpoint(tcp::v4(), static_cast<asio::ip::port_type>(param.Port)),
	m_pDstEndpoint(asio::ip::address::from_string(param.DstIP), static_cast<asio::ip::port_type>(param.DstPort)),
	m_iMaxLength(param.MaxLength),
	m_pContext(std::make_unique<asio::io_context>())
{
	try
	{
		m_pSocket = std::make_unique<tcp::socket>(*m_pContext);
		m_pResolver = std::make_unique<tcp::resolver>(*m_pContext);
		asio::error_code error;
		asio::connect(*m_pSocket, m_pResolver->resolve(m_pDstEndpoint, error));

	}
	catch (std::exception& e)
	{
		std::cout << "Error Closing Socket" << e.what() << std::endl;
		std::cout << "create tcp ip:127.0.0.1:" + std::to_string(param.DstPort) + " failed!!!" << std::endl;
	}
}

bool hs::net::TCPSender::Send(const Packet& packet) noexcept
{
	try {
		auto length = asio::write(*m_pSocket, asio::buffer(packet.Data, packet.Length));
		if (length > 0) return true;
	}
	catch (std::exception& e)
	{
		std::cout << "Error Closing Socket" << e.what() << std::endl;
	}
	return false;
}

bool hs::net::TCPSender::Close() noexcept
{
	if (m_pSocket->is_open())
	{
		m_pSocket->shutdown(asio::ip::tcp::socket::shutdown_both);
		m_pSocket->close();
	}
	return true;
}
