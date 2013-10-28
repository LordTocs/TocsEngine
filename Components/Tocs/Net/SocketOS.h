#pragma once

#ifdef WIN32
//#include <WinSock.h>
#include <WinSock2.h>
#include <ws2ipdef.h>
#include <ws2tcpip.h>
#define NOMINMAX
#include <Windows.h>


#else
#include <sys/socket.h>
#endif