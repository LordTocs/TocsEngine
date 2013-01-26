#pragma once
#include <string>

namespace Tocs {
namespace Net {

class PacketType
{
	enum InternalEnum
	{
		reliable,
		unreliable
	};
	InternalEnum Internal;

	PacketType (InternalEnum format) : Internal (format) {}

public:
	const static PacketType Reliable;
	const static PacketType UnReliable;

	PacketType () : Internal (reliable) {}

	bool operator ==  (const PacketType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const PacketType &op2) const {return Internal != op2.Internal;}

	std::string ToString () const;

	friend class Socket;
};

}}

