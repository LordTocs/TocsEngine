#pragma once

#include <string>

namespace Tocs {
namespace Net {

class IPAddress
{

public:
	unsigned char AddressBytes[4];
	IPAddress();
	IPAddress(std::string hostname);
	IPAddress(unsigned int addr);
	IPAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
	std::string ToString ();

	bool operator < (const IPAddress &op2) const;

	unsigned int ToInteger () const;

};

}}