#include <enet\enet.h>
#include "OutgoingPacket.h"

namespace Tocs {
namespace Net {

OutgoingPacket::OutgoingPacket(const PacketType &type)
	: Type (type)
{}

ENetPacket *OutgoingPacket::GetInternalPacket () const
{
	enet_uint32 flags = ENET_PACKET_FLAG_NO_ALLOCATE;
	if (Type == PacketType::Reliable)
	{
		flags |= ENET_PACKET_FLAG_RELIABLE;
	}
	return enet_packet_create (Data.GetData (),Data.Length (), flags);
}

void OutgoingPacket::Write (int location, char *data, int size) 
{
	Data.Write (location,data,size); 
}
void OutgoingPacket::Read  (int location, char *data, int size) 
{ 
	Data.Read  (location,data,size); 
}
bool OutgoingPacket::CanWrite (int location, int size) const    
{ 
	return Data.CanWrite(location,size); 
}
bool OutgoingPacket::CanRead  (int location, int size) const    
{ 
	return Data.CanRead(location,size); 
}

}}