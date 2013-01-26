#pragma once
#include "IPAddress.h"

namespace Tocs {
namespace Net {

class Endpoint
{
	IPAddress Address;
	unsigned short Port;
public:
	Endpoint();
	Endpoint(const IPAddress &addr, unsigned short Port);
	
	const IPAddress &GetAddress () const { return Address; }
	unsigned short GetPort () const { return Port; }
};

}}