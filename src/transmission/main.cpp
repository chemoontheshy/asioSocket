#include "transmission.h"

enum class Type
{
    SENDER,
    RECEIVER,
};

int main(int argc, char* argv[])
{
    Type type = Type::SENDER;
    switch (type)
    {
    case Type::SENDER:
    {
        hs::net::SenderParam param;
        param.DstIP = "127.0.0.1";
        param.DstPort = 6000;
        param.Port = 4200;
        param.MaxLength = 1024;
        param.Type = hs::net::NetType::TCP;
        auto sender = hs::net::CreateSender(param);
        Packet packet;
        char data[1024] = "1234";
        packet.Data = reinterpret_cast<uint8_t*>(data);
        packet.Length = 4;
        size_t count = 0;
        while (true)
        {
            if (!sender->Send(packet))
            {
                std::cout << "err" << std::endl;
                break;
            }
            else
            {
                std::cout << count++ << std::endl;
            }
            vsnc::utils::__sleep_milliseconds(1000);
        }
        sender->Close();
    }
        break;
    case Type::RECEIVER:
    {
        hs::net::ReceiverParam param;
        param.MaxLength = 1024;

        param.Port = 6000;
        param.Type = hs::net::NetType::TCP;
        auto receiver = hs::net::CreateReceiver(param);
        Packet packet;
        char data[1024];
        packet.Data = reinterpret_cast<uint8_t*>(data);
        packet.Length = 1024;
        while (true)
        {
            while (receiver->Read(packet))
            {

                std::string msg(reinterpret_cast<char*>(packet.Data), packet.Length);

                std::cout << msg << std::endl;
            }
            vsnc::utils::__sleep_milliseconds(10);
        }
        receiver->Close();

    
    }
    default:
        break;
    }
   
    return 0;
}
