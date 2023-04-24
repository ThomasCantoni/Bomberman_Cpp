#pragma once
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include "byteconverter.h"

//COMMUNICATION PROTOCOL
// 
// ENVELOPE PACKET DEFINITION:
// FIRST 4 BYTES	: OBJECT ID
// bytes 4 TO 8		: NET COMMAND
// FROM 8 ONWARDS	: DATA PAYLOAD

enum NetCommand
{
	Update = 0,
	Announce = 1,
	Death = 2,
	EggSpawn=3,
	UpdateMapStatus=4,
	ChangeMap=5
};


static bool SetSocketBlockingEnabled(int fd, bool blocking)
{
	if (fd < 0) return false;

#ifdef _WIN32
	unsigned long mode = blocking ? 0 : 1;
	return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1) return false;
	flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
	return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}
