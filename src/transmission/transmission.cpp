#include "transmission.h"
#include "imp_transmission.h"

using namespace hs::net;


std::shared_ptr<Receiver> hs::net::CreateReceiver(const ReceiverParam& __VSNC_IN param)
{
	return std::shared_ptr<Receiver>(new IMPReceiver(param));
}
