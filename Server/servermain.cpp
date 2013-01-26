#include <iostream>
#include <Tocs/Net/Server.h>
#include <Tocs/Core/BinaryManipulator.h>
using namespace Tocs;
using namespace Tocs::Net;
using namespace std;

void OnIncomingPacket(IncomingPacket &packet)
{
	cout << "Packet Received! " << packet.Length ();
	BinaryManipulator bm (packet);
	cout << bm.Read <int> () << " " << bm.Read <int> () << endl;
}

void OnClientConnect (Socket &sock)
{
	cout << "Client Connected!";
	sock.OnPacketRecv = std::function<void(IncomingPacket&)> (OnIncomingPacket);
}

int main ()
{
	cout << "Starting Server." << endl;
	Server testserver;
	testserver.OnClientConnected = std::function<void (Socket &)>(OnClientConnect);
	testserver.Start (8888,10);

	while (true)
	{
		testserver.Service (1);
	}
	return 0;
}