#pragma once
#include "NetworkManager.h"
#include "Player.h"
#include "Map.h"
namespace Bomberman
{

	SOCKET						NetworkManager::Server_socket;
	sockaddr_in					NetworkManager::Server_addr;
	WSADATA						NetworkManager::wsa;
	int							NetworkManager::id,NetworkManager::MapIndex;
	unsigned char				NetworkManager::message[1024];
	float						NetworkManager::secondAccumulator;
	const Player*				NetworkManager::LocalPlayer;
	std::vector<OnlinePlayer*>  NetworkManager::OnlinePlayers;
	std::vector<Transform*>		NetworkManager::ObjectsToSync;
	std::vector<NetworkManager::NetworkOp>		NetworkManager::NetworkOps;
	std::queue<unsigned char>	NetworkManager::PacketBuffer;

	MulticastDelegate<int> NetworkManager::MapIndexReceived;
	

	

	int NetworkManager::SetNonBlocking(int s)
	{
#ifdef _WIN32
		unsigned long nb_mode = 1;
		return 0; //ioctlsocket(s, FIONBIO, &nb_mode);
#else
		int flags = fcntl(s, F_GETFL, 0);
		if (flags < 0)
			return flags;
		flags |= O_NONBLOCK;
		return fcntl(s, F_SETFL, flags);
#endif
	}


	unsigned char* NetworkManager::Initialize(const char* server_ip, const int port,const Player* LocalPlayer)
	{
		
		NetworkManager::LocalPlayer = LocalPlayer;
		NetworkOps = std::vector<NetworkManager::NetworkOp>(4);

		NetworkOps[0] = &NetworkManager::UpdateOnlinePlayer;
		NetworkOps[1] = &NetworkManager::InstantiatePlayer;
		NetworkOps[2] = &NetworkManager::KillOnlinePlayer;
		NetworkOps[3] = &NetworkManager::InstantiateEgg;
		//auto ip = "37.100.40.129";
		//auto port = 8888;

		auto ip = server_ip;


		// Initialize Winsock
		printf("\nInitializing Winsock...");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("Failed. Error Code : %d", WSAGetLastError());
			exit(-1);
		}
		printf("Initialized.\n");

		// Create a socket
		Server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (Server_socket < 0)
		{
			printf("Could not create socket : %d", WSAGetLastError());
		}
		printf("Socket created.\n");

		// Prepare the sockaddr_in structure
		memset(&Server_addr, 0, sizeof(Server_addr));
		Server_addr.sin_family = AF_INET;

		printf("\n%d\n", port);
		Server_addr.sin_port = htons(port);
		inet_pton(AF_INET, ip, &Server_addr.sin_addr);

		// Connect to server
		//bind_error = connect(Server_socket, (struct sockaddr *)&Server_addr, sizeof(struct sockaddr_in));
		//if (bind_error != 0)
		//{
		//    printf("Connect failed with error code : %d", WSAGetLastError());
		//    exit(-1);
		//}
		//printf("Connected.\n");
		char data[] = { 0x00,0x00,0x00,0x00 };
		char data2[8];

		int sent_bytes = -1;
		int received_bytes = -1;
		int server_size = sizeof(Server_addr);
		 sent_bytes = sendto(Server_socket, data, 4, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		 
		while (received_bytes == -1)
		{
			received_bytes = recvfrom(Server_socket, data2, 8, 0, (struct sockaddr*)&Server_addr, &server_size);

		}
			
		

		id = byteconverter::BytesToInt((unsigned char*)data2,0,false);
		MapIndex= byteconverter::BytesToInt((unsigned char*)data2, 4,false);
		MapIndexReceived.Broadcast(MapIndex);
		
		printf(" MY PLAYER-ID = %i\n", id);
		SetNonBlocking(Server_socket);
		//player.ID = id;
		//message = calloc(1, 50);
	}

	/// <summary>
	/// Send a series of bytes to the IP Server_Socket
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int NetworkManager::SendToServer(unsigned char* data)
	{
		int sent_bytes = sendto(Server_socket, (char*)data, 50, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		if (sent_bytes < 0)
		{
			puts("Send failed");
			return 1;
		}
		return 0;

	}
	unsigned long NetworkManager::GetIncomingPacketNumber()
	{
		unsigned long msg_length;
		int error = ioctlsocket(Server_socket, FIONREAD, &msg_length);

		return msg_length;
	}
	int  NetworkManager::ReceiveFromServer(unsigned char* buffer, int buffer_length)
	{
		int server_size = sizeof(Server_addr);
		return recvfrom(Server_socket, (char*)buffer, buffer_length, 0, (struct sockaddr*)&(Server_addr), &server_size);
	}
	int  NetworkManager::ProcessMessage(const unsigned char* message, const int msg_length)
	{
		//for (int i = 0; i < msg_length; ++i)
		//{
		//	printf("%x", message[i]);
		//}

		int player_id = byteconverter::BytesToInt(message, 0);


		printf("\n RECEIVED PLAYERID %i \n", player_id);

		int commandCode = byteconverter::BytesToInt(message, 4);
		printf("\n RECEIVED COMMAND %i \n", commandCode);
		NetworkOp methodToCall = NetworkOps[commandCode];
		(*methodToCall)(message, player_id);


		return 0;
	}
	void NetworkManager::ManageNetworkOperations()
	{
		unsigned char* Network_ID	;//[sizeof(float)];
		unsigned char* command		;//[sizeof(int)];
		unsigned char* buffer_x		;//[sizeof(float)];
		unsigned char* buffer_y		;//[sizeof(float)];

		secondAccumulator += Time::DeltaTime;
		if (secondAccumulator > NETWORK_PERIOD)
		{
			secondAccumulator = 0;
			Network_ID = byteconverter::IntToBytes(id);
			Vector2 pos = LocalPlayer->transform.GetPosition();
			buffer_x = byteconverter::FloatToBytes( pos.x);
			buffer_y = byteconverter::FloatToBytes( pos.y);
			command = byteconverter::IntToBytes(0);


			memcpy(message, Network_ID, sizeof(int));
			byteconverter::BytesAppend(message, 50, 4, command, sizeof(int));

			byteconverter::BytesAppend(message, 50, 8, buffer_x, sizeof(float));
			byteconverter::BytesAppend(message, 50, 12, buffer_y, sizeof(float));
			std::cout << std::endl;
			for (int i = 0; i < 16; ++i)
			{
				printf("|%X", message[i]);
			}
			std::cout << std::endl;
			int queueLength = PacketBuffer.size();
			for (int i = 0; i < queueLength; i++)
			{
				unsigned char c = PacketBuffer.front();
				byteconverter::BytesAppend(message, 1024, 16 + i, c);
				PacketBuffer.pop();
			}
			SendToServer(message);
			
		}
		// get info from server
		for (int i = 0; i < 500; ++i)
		{


			unsigned long msg_length = GetIncomingPacketNumber();
			if (msg_length == 0)
				return;


			int n = ReceiveFromServer(message, MSG_SIZE);
			if (n == 0)
				return;
			//printf("Received %d bytesfrom %s : %d : %.*s \n", n, inet_ntop(NM->Server_addr.sin_addr), ntohs(NM->Server_addr.sin_port), n, message);
			NetworkManager::ProcessMessage(message, n);
		}
	}
	void NetworkManager::InstantiateEgg(const unsigned char* message, int playerID)
	{
		float X, Y;
		X = byteconverter::BytesToFloat(message, 8, true);
		Y = byteconverter::BytesToFloat(message, 12, true);
		auto new_egg = std::make_unique<Eggbomb*>(new Eggbomb(X, Y));
	}
	void NetworkManager::InstantiatePlayer(const unsigned char* message, int playerID)
	{
		OnlinePlayer* newPlayer = new OnlinePlayer(playerID);

		OnlinePlayers[newPlayer->ID - 1] = newPlayer;
	}
	void NetworkManager::UpdateOnlinePlayer(const unsigned char* message, int playerID)
	{
		if (playerID == id)
			return;
		OnlinePlayer* playerSelected = OnlinePlayers[playerID - 1];
		float printX, printY;
		printX = byteconverter::BytesToFloat(message, 8, true);
		printY = byteconverter::BytesToFloat(message, 12, true);


		playerSelected->old_position.x = playerSelected->latest_position.x;
		playerSelected->old_position.y = playerSelected->latest_position.y;
		playerSelected->latest_position.x = printX;
		playerSelected->latest_position.y = printY;
		playerSelected->lerp_accumulator = 0;
		//std::cout << "#################################################" << std::endl;
		//std::cout << "UPDATE PLAYER" << std::endl;
		//std::cout << "Player ID = " << player_id << std::endl;
		//std::cout << "POSITIONS : " << printX << " " << printY << std::endl;
		//std::cout << "#################################################" << std::endl;
	}
	void NetworkManager::KillOnlinePlayer(const unsigned char* message, int playerID)
	{
		OnlinePlayer* playerSelected = OnlinePlayers[playerID - 1];
		OnlinePlayers[playerID - 1] = NULL;
		UpdateMgr::RemoveItem(playerSelected);
	}
	void NetworkManager::SendEggRequest(const Vector2 pos)
	{
		//Eggbomb* egg = new Eggbomb(this);
		unsigned char* Network_ID;
		unsigned char* command; 
		unsigned char* bufferX; 
		unsigned char* bufferY;

		bufferX =		byteconverter::FloatToBytes(pos.x);
		bufferY =		byteconverter::FloatToBytes(pos.y);
		Network_ID =	byteconverter::IntToBytes(id);
		command =		byteconverter::IntToBytes(3);
		
		unsigned char msg[16];
		memcpy(msg, Network_ID, sizeof(int));
		byteconverter::BytesAppend(msg, 50, 4, command, sizeof(int));
		byteconverter::BytesAppend(msg, 50, 8, bufferX, sizeof(float));
		byteconverter::BytesAppend(msg, 50, 12, bufferY, sizeof(float));
		EnqueuePacket(msg,16);
	}
	void NetworkManager::EnqueuePacket(unsigned char* data, int bytesToInsert)
	{
		for (int i = 0; i < bytesToInsert; i++)
		{
			PacketBuffer.push(data[i]);

		}
	}
};
