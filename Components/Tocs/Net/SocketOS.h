#pragma once

#ifdef WIN32
//#include <WinSock.h>
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#include <Windows.h>


#else
#include <sys/socket.h>
#endif