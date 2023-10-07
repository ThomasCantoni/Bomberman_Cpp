#pragma once

#include "NetworkBase.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include "OnlinePlayer.h"
#include "Delegates.h"
#include "NetworkPacket.h"
namespace Bomberman
{
	class Player;
	class Map;

	/// <summary>
	/// This class is responsible for every communication and interaction with the server.
	/// The server is authorithative and can decide in its power, clients obey.
	/// Messages are sent to the server only once a while to not overwork the network. This is done using a queue.
	/// </summary>
	
	class BombermanClientMgr
	{
		typedef int(*NetworkCommandGeneric)(const NetworkPacket);
		

		//DECLARATION SYNTAX FOR FOR NON STATIC CLASSES WOULD BE:
		//typedef void(<Class>::*NetworkOp)(const unsigned char*, int);

	private:
		static std::unordered_map<int, NetworkCommandGeneric>	NETCOMMANDS;


	public:
		static Map* currentMap;
		static MulticastDelegate<int,int,Vector2,Vector2> ServerConnectionEstablished;
		
		static float secondAccumulator;
		static SOCKET Server_socket;
		static sockaddr_in Server_addr;
		static WSADATA wsa;
		
		static int MapIndex;
		static std::vector<unsigned char> message;

		static std::unordered_map<int,Transform*> TransformsToSync; //this map is for the received transforms relative to item ID
		static std::unordered_map<int, OnlinePlayer*> OnlinePlayers;//this is for the OnlinePlayer local entity relative to item ID

		static std::queue<unsigned char> PacketBuffer;
		


		static unsigned char* Initialize(const char* server_ip, const int port);

		static int SendQueueToServer();


		static unsigned long GetIncomingPacketNumber();
		static std::shared_ptr<std::vector<NetworkPacket>> ReceiveFromServer(std::vector<unsigned char>* buffer,int* length);
		static void EnqueuePacket(unsigned char* data, int lengthToInsert);
		static void EnqueuePacket(std::vector<unsigned char>* data, int lengthToInsert);

		static void Update();
		static int  ProcessMessage(const std::shared_ptr<std::vector<NetworkPacket>> message, const int msg_length);
		static void SendEggRequest(const Vector2 pos);

		static int UpdateOnlinePlayer	(const NetworkPacket message);
		static int InstantiateEgg		(const NetworkPacket message);
		static int InstantiatePlayer	(const NetworkPacket message);
		static int KillOnlinePlayer		(const NetworkPacket message);
		static int Travel				(const NetworkPacket message);
	
		


	};
}