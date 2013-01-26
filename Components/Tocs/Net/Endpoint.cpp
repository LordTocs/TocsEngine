#include "Endpoint.h"


namespace Tocs {
namespace Net {

Endpoint::Endpoint(void)
	: Port (0)
{
}

Endpoint::Endpoint (const IPAddress &addr, unsigned short port)
	: Address (addr),
	  Port (port)
{

}

}}