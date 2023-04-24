#pragma once
#include "NetworkBase.h"

#include "PlayerData.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <WinSock2.h>
#include <unordered_set>

//#include <functional>
#include "Delegates.h"
#define MAX_PACKET_SIZE 256

namespace Bomberman
{

	
class Server
{
	typedef void(*NetworkOp)(const unsigned char*, int);
public:
private:
	static std::vector<NetworkOp> NetworkOps;
public:
	
	
	static int currentMap,PlayerCount,maxPacketSize;
	static SOCKET ServerSocket;
	static sockaddr_in IncomingClient,ServerAddress;
	static WSADATA wsa;
	static unsigned char message[256];
	//static std::vector<OnlinePlayer*> OnlinePlayers;
	static std::vector<std::shared_ptr<ActorData>> ObjectsToSync;
	//static std::vector<pollfd>ExistingConnections;
	static std::map<unsigned int, std::shared_ptr<PlayerData>> knownClients;
	static std::unordered_set<unsigned int> blacklistedClients;
	

	static std::vector<std::string> MapNames;



    static void Initialize(std::string address,int port,int mapIndex=0,int max_packet_size = 1024);
	static int SetMap(int MapIndex);
	static int LoadMap(int MapIndex);
	static void Run();
	static void CheckStatus();
	static void ProcessMessage(sockaddr_in client);
	static bool CheckClient(sockaddr_in client);
	static void AcceptClient(sockaddr_in client);
	

	static void SendWorldStatus(sockaddr_in ToExclude);

	static bool CheckIfBlacklisted(const unsigned int client);
	static void BlacklistClient(const unsigned int toBlacklist);
};


}