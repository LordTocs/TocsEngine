#include <enet/enet.h>
#include "IncomingPacket.h"

namespace Tocs {
namespace Net {

IncomingPacket::~IncomingPacket() 
{
	enet_packet_destroy (InternalPacket);
}

void IncomingPacket::Read  (int location, char *data, int size)
{
	::memcpy (data,InternalPacket->data + location,size);
}

int IncomingPacket::Length () const
{ 
	return InternalPacket->dataLength;
}

}}