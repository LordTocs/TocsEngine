#include <enet/enet.h>
#include "Socket.h"
#include <Tocs/Core/StaticInitializer.h>



namespace Tocs {
namespace Net {

void InitSockets ()
{
	enet_initialize ();
}
//StaticInitializer netinit (StaticInitializer::InitDelegate::FromFunction <&InitSockets> ());

	
Socket::Socket()
	: Client (enet_host_create (0,1,2,0,0)),
	  Peer(nullptr)
{

}

Socket::Socket (ENetPeer *peer)
	: Peer (peer),
	  Client (nullptr)
{
}
Socket::~Socket()
{
	if (Client != nullptr)
		enet_host_destroy (Client);
}

void Socket::Send (const OutgoingPacket &packet)
{
	if (Peer != nullptr)
	{
		enet_peer_send (Peer,0,packet.GetInternalPacket ());
	}
}

void Socket::Service ()
{
	if (Client == nullptr)
		return;

	ENetEvent ev;

	while (enet_host_service (Client,&ev,0) > 0)
	{
		if (ev.type == ENET_EVENT_TYPE_RECEIVE)
		{
			IncomingPacket packet (ev.packet);
			OnPacketRecv (packet);
		}
		if (ev.type == ENET_EVENT_TYPE_DISCONNECT)
		{
			OnDisconnect ();
		};
	}
}

bool Socket::Connect (const Endpoint &endpoint)
{
	if (Client == nullptr)
		return false;

	ENetAddress addr;
	//addr.host = //endpoint.GetAddress ().ToInteger ();
	enet_address_set_host (&addr,"localhost");
	addr.port = endpoint.GetPort ();
	Peer = enet_host_connect (Client,&addr,2,0);
	if (Peer == nullptr)
		return false;
	
	ENetEvent ev;
	if (enet_host_service (Client,&ev,1000) <= 0)
	{
		enet_peer_reset (Peer);
		return false;
	}
	
	if (ev.type == ENET_EVENT_TYPE_CONNECT)
	{
		enet_host_flush (Client);
		return true;
	}

	return false;
}

}}