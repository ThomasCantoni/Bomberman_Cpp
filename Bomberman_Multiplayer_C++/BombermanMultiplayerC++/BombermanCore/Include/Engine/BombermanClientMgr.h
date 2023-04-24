#pragma once

#include "NetworkBase.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
//#include <functional>

#include "OnlinePlayer.h"
#include "Delegates.h"

namespace Bomberman
{
	class Player;
	class Map;

	class BombermanClientMgr
	{
		typedef void(*NetworkOp)(const unsigned char*, int);
		//DECLARATION SYNTAX FOR FOR NON STATIC CLASSES WOULD BE:
		//typedef void(<Class>::*NetworkOp)(const unsigned char*, int);

	private:
		static std::vector<NetworkOp> NetworkOps;
	public:
		static Map* currentMap;
		static MulticastDelegate<int> MapIndexReceived;
		static MulticastDelegate<void> ClientReady;

		static std::queue<unsigned char> PacketBuffer;
		//static std::function<void(int)> test;
		static const Player* LocalPlayer;
		static float secondAccumulator;
		static SOCKET Server_socket;
		static sockaddr_in Server_addr;
		static WSADATA wsa;
		static int id,MapIndex;
		static unsigned char message[1024];
		static std::vector<OnlinePlayer*> OnlinePlayers;
		static std::vector<Transform*> ObjectsToSync;
		//THIS IS SIMILAR TO DECLARING A DELEGATE IN C#


		static unsigned char* Initialize(const char* server_ip, const int port,const  Player* LocalPlayer);

		/// <summary>
		/// DEPRECATED Send a series of bytes to the IP Server_Socket
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		static int OLD_SendToServer(unsigned char* data);
		static int SendQueueToServer();


		static unsigned long GetIncomingPacketNumber();
		static int ReceiveFromServer(unsigned char* buffer, int buffer_length);
		static void EnqueuePacket(unsigned char* data, int lengthToInsert);


		static void Update();
		static int ProcessMessage(const unsigned char* message, const int msg_length);
		static void SendEggRequest(const Vector2 pos);

		static void UpdateOnlinePlayer(const unsigned char* message, int playerID);
		static void InstantiateEgg(const unsigned char* message, int playerID);
		static void InstantiatePlayer(const unsigned char* message, int playerID);
		static void KillOnlinePlayer(const unsigned char* message, int playerID);
		//void OnCollide(Collision* collisionInfo) override;
		static void test();
	};
}