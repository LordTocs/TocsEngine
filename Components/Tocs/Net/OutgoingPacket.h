#pragma once
#include <Tocs/Core/DataSource.h>
#include <Tocs/Core/DynamicByteBuffer.h>
#include <string>
#include "EnetForwardRefs.h"
#include "PacketType.h"



namespace Tocs {
namespace Net {

class OutgoingPacket : public DataSource
{
	PacketType Type;
	DynamicByteBuffer Data;

	ENetPacket *GetInternalPacket () const;
public:
	OutgoingPacket(const PacketType &type);

	void Write (int location, char *data, int size);
	void Read  (int location, char *data, int size);
	bool CanWrite (int location, int size) const;
	bool CanRead  (int location, int size) const;   

	friend class Socket;
};

}}