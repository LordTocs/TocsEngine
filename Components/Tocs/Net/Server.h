#pragma once
#include <functional>
#include "Socket.h"
#include "EnetForwardRefs.h"

namespace Tocs {
namespace Net {

class Server
{
	ENetHost *Host;
public:
	Server ();
	~Server ();

	void Start (unsigned short port, int clients);

	std::function <void (Socket &)> OnClientConnected;
	std::function <void (Socket &)> OnClientDisconnected;

	void Service (int timeout);

};

}}