#pragma once
#include <string>
#include "EnetForwardRefs.h"
#include "PacketType.h"
#include <Tocs/Core/DataSource.h>

namespace Tocs {
namespace Net {

class IncomingPacket : public DataSource
{
	PacketType Type;
	
	ENetPacket *InternalPacket;
	IncomingPacket(const IncomingPacket &op2){}
	IncomingPacket(ENetPacket *packet) : InternalPacket (packet) {}
public:
	

	~IncomingPacket();// {enet_packet_destroy (InternalPacket);}

	int Length () const;// { return InternalPacket->dataLength; }

	void Write (int, char *, int) {}
	void Read  (int location, char *data, int size);// {::memcpy (data,InternalPacket->data + location,size);}
	bool CanWrite (int location, int size) const {return false;}
	bool CanRead  (int location, int size) const {return location >= 0 && location + size <= Length ();}

	friend class Socket;
	friend class Server;
};

}}