#include "IPAddress.h"
#include "SocketOS.h"
using namespace std;

namespace Tocs {
namespace Net {

IPAddress::IPAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
	AddressBytes[0] = a;
	AddressBytes[1] = b;
	AddressBytes[2] = c;
	AddressBytes[3] = d;
}

IPAddress::IPAddress()
{
	memset (AddressBytes,0,4);
}

IPAddress::IPAddress(unsigned int addr)
{
	memcpy (AddressBytes,&addr,4);
}

IPAddress::IPAddress (string hostname)
{
	struct addrinfo hints, *info;

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_protocol = SOCK_STREAM;

	int result = getaddrinfo(hostname.c_str (), "8180", &hints, &info);

	if (result != 0)
	{
		throw "Failed to retreive hostname";
	}

	if (info->ai_family == AF_INET)
	{
		sockaddr_in *ipv4 = reinterpret_cast <sockaddr_in *> (info->ai_addr);
		memcpy (AddressBytes,&ipv4->sin_addr,4);
	}

	freeaddrinfo (info);
}


bool IPAddress::operator< (const IPAddress &op2) const
{
	return AddressBytes[0] < op2.AddressBytes[0] &&
		   AddressBytes[1] < op2.AddressBytes[1] &&
		   AddressBytes[2] < op2.AddressBytes[2] &&
		   AddressBytes[3] < op2.AddressBytes[3];
}

unsigned int IPAddress::ToInteger () const
{
	return *reinterpret_cast <const unsigned int *> (&AddressBytes[0]);
}


}}