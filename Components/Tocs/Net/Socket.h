#pragma once
#include "OutgoingPacket.h"
#include "IncomingPacket.h"
#include "Endpoint.h"
#include "EnetForwardRefs.h"
//#include <Tocs/Core/Delegate.h>
#include <functional>


namespace Tocs {
namespace Net {

class Socket
{
	ENetHost *Client;
	ENetPeer *Peer;
	void *Tag;

	Socket (ENetPeer *peer);
public:
	Socket();
	~Socket();

	std::function <void (IncomingPacket &)> OnPacketRecv;
	std::function <void ()> OnDisconnect;

	void Send (const OutgoingPacket &packet);

	void Service ();

	bool Connect (const Endpoint &endpoint);

	template <class T>
	void SetTag (T *tag)
	{ Tag = tag; }

	template <class T>
	T *GetTag ()
	{ return reinterpret_cast <T *> (Tag); }

	friend class Server;
};

}}

