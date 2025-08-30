#pragma once
#include "NetworkBase.h"

#include "PlayerData.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <WinSock2.h>
#include <unordered_set>
#include "NetworkPacket.h"
//#include <functional>
#include "Delegates.h"


namespace Bomberman
{
	
	
class Server
{
	typedef int(*NetworkCommandGenericServer)(sockaddr_in,NetworkPacket);


private:

	static std::unordered_map<int, NetworkCommandGenericServer>	ServerNETCOMMANDS;

public:
	
	
	static int currentMap,PlayerCount,maxPacketSize;
	static SOCKET ServerSocket;
	static sockaddr_in IncomingClient,ServerAddress;
	static WSADATA wsa;
	static std::vector<unsigned char> message;
	
	static std::map<unsigned int, std::shared_ptr<ServerActor>> ObjectsToSync;
	static std::map<ServerActor*,unsigned int> ActorToID;

	static std::map<unsigned int, std::shared_ptr<PlayerData>> knownClients;
	static std::unordered_set<unsigned int> blacklistedClients;
	

	static std::vector<std::string> MapNames;



    static void Initialize(std::string address,int port,int mapIndex=0,int max_packet_size = 1024);
	static int SetMap(int MapIndex);
	static int LoadMap(int MapIndex);
	static void Run();
	static void ProcessMessage(sockaddr_in client,const std::shared_ptr<std::vector<NetworkPacket>> msg,int length);

	static void CheckClientStatus();
	static bool CheckClientPassword	(sockaddr_in client);
	static bool IsClientBlacklisted	(sockaddr_in client);
	static bool IsClientKnown		(sockaddr_in client);
	static void AcceptClient		(sockaddr_in client);
	static void BlacklistClient		(sockaddr_in toBlacklist);
	static void SendToClient		(sockaddr_in clientDestination);

	static void SendWorldStatus(sockaddr_in client);
	static int ReceiveInput(sockaddr_in Client, const NetworkPacket msg);
};


}