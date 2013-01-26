#include <enet\enet.h>
#include "Server.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Net {

Server::Server()
	: Host (nullptr)
{
	
}

void Server::Start (unsigned short port, int clients)
{
	ENetAddress addr;
	addr.host = ENET_HOST_ANY;//IPAddress(192,168,1,100).ToInteger ();
	addr.port = port;
	Host = enet_host_create (&addr,clients,2,0,0);
	if (Host == nullptr)
	{
		std::cout << "Error creating host" << std::endl;
	}
	else
	{
		cout << "Host: " << Host << endl << "HostAddr: " << Host->address.host << endl;
	}
}


Server::~Server(void)
{
	if (Host != nullptr)
		enet_host_destroy (Host);
}

void Server::Service (int timeout)
{
	ENetEvent ev;

	//cout << "Service!" << endl;

	int result = 0;
	do
	{
		result = enet_host_service (Host, &ev,timeout);
		if (result <= 0)
			return;
		cout << "Event" << endl;
		if (ev.type == ENET_EVENT_TYPE_CONNECT)
		{
			Socket *sock = new Socket (ev.peer);
			ev.peer->data = sock;
			OnClientConnected(*sock);
		}
		if (ev.type == ENET_EVENT_TYPE_RECEIVE)
		{
			Socket *sock = reinterpret_cast<Socket *> (ev.peer->data);
			sock->OnPacketRecv (IncomingPacket (ev.packet));
		}
		if (ev.type == ENET_EVENT_TYPE_DISCONNECT)
		{
			Socket *sock = reinterpret_cast<Socket *> (ev.peer->data);
			OnClientDisconnected (*sock);
			delete sock;
		}
	}while (true);

	if (result < 0)
		cout << "FFFFF" << endl;
	
}

}}