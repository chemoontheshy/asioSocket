#include "transmission.h"

int main(int argc, char* argv[])
{
    hs::net::ReceiverParam param;
    param.MaxLength = 1024;

    param.Port = 6000;
    param.Type = hs::net::NetType::TCP;
    auto socket = hs::net::CreateReceiver(param);
    Packet packet;
    char data[1024];
    packet.Data = reinterpret_cast<uint8_t*>(data);
    packet.Length = 1024;
    while (true)
    {
        while (socket->Read(packet))
        {

            std::string msg(reinterpret_cast<char*>(packet.Data), packet.Length);

            std::cout << msg << std::endl;
        }
        vsnc::utils::__sleep_milliseconds(10);
    }
    return 0;
}
