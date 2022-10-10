#ifndef __HS_TRANSMISSION_H__
#define __HS_TRANSMISSION_H__

#include "utils/vsnc_utils.h"


using vsnc::stucture::Packet;

namespace hs
{
	namespace net
	{
		
		/// <summary>
		/// ��������
		/// </summary>
		enum class NetType
		{
			// TCP
			TCP,
			// UDP
			UDP
		};

		/// <summary>
		/// ������
		/// </summary>
		class Receiver
		{
		public:
			/// <summary>
			/// ������
			/// </summary>
			virtual ~Receiver() = default;
			
			/// <summary>
			/// ���պ���
			/// </summary>
			/// <param name="packet">���ݰ�</param>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			virtual bool Read(Packet& __VSNC_IN_OUT packet) noexcept = 0;
		};
		class Sender
		{
		public:
			/// <summary>
			/// ��������
			/// </summary>
			virtual ~Sender() = default;

			/// <summary>
			/// ������
			/// </summary>
			/// <param name="packet">���ݰ�</param>
			/// <returns>�ɹ�����true�����󷵻�false</returns>
			virtual bool Send(const Packet& __VSNC_IN packet) noexcept = 0;
		};

		/// <summary>
		/// ��������������
		/// </summary>
		struct ReceiverParam
		{

			/// ��������
			NetType  Type;
			/// ���ض˿�
			uint16_t Port;
			/// ������󳤶�
			size_t   MaxLength;
		};

		std::shared_ptr<Receiver> CreateReceiver(const ReceiverParam& __VSNC_IN param);

		/// <summary>
		/// ����������
		/// </summary>
		struct SenderParam
		{
			/// ��������
			NetType     Type;
			/// ���ض˿� :Ϊ0ʱ��ϵͳ���䣬��Ϊ0���ָ��
			uint16_t    Port;
			/// Ŀ��IP
			std::string DstIP;
			/// Ŀ��Port
			uint16_t    DstPort;
			/// ������󳤶�
			size_t      MaxLength;
		};
	}
}

#endif // !__HS_TRANSMISSION_H__

