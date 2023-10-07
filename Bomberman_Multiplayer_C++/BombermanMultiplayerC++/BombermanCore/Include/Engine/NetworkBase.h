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
#define NETWORK_PERIOD 0.03f
#define MAX_PACKET_SIZE 1024 //0x400
//#define PACKET_DELIMITER 0x7c
enum NETCOMMANDType // this type of command has object ID and payload
{
	Update = 0,		//update an actor in the scene according to ID
	Announce = 1,	//instantiate new player and set specified local ID
	Death = 2,		//destroy player with specified local ID
	EggSpawn=3,		//instantiate egg bomb in the world at the position of the player with ID.
	UpdateLocalPlayer = 4,	//physics are computed on the server, this command updates the local player position according to those physics.
							//new positions are contained in payload.
	PlayerInput = 5,		//player input is sent to the server and is then validated. Important for physics related movement.
	ChangeMap=6,			// tell the local machine to change map
	COUNT

};
enum PlayerInputType
{
	Movement,
	EggRequest
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
