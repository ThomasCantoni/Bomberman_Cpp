#pragma once
#include "BombermanClientMgr.h"
#include "Player.h"
#include "Map.h"

namespace Bomberman
{


	SOCKET						BombermanClientMgr::Server_socket;
	sockaddr_in					BombermanClientMgr::Server_addr;
	WSADATA						BombermanClientMgr::wsa;
	int							BombermanClientMgr::id;
	unsigned char				BombermanClientMgr::message[1024];
	float						BombermanClientMgr::secondAccumulator;
	const Player*				BombermanClientMgr::LocalPlayer;
	std::vector<OnlinePlayer*>  BombermanClientMgr::OnlinePlayers;
	std::vector<Transform*>		BombermanClientMgr::ObjectsToSync;
	std::vector<BombermanClientMgr::NetworkOp>		BombermanClientMgr::NetworkOps;
	std::queue<unsigned char>	BombermanClientMgr::PacketBuffer;

	MulticastDelegate<int> BombermanClientMgr::MapIndexReceived;


	unsigned char* BombermanClientMgr::Initialize(const char* server_ip, const int port, const Player* LocalPlayer)
	{

		BombermanClientMgr::LocalPlayer = LocalPlayer;
		NetworkOps = std::vector<BombermanClientMgr::NetworkOp>(4);

		NetworkOps[0] = &BombermanClientMgr::UpdateOnlinePlayer;
		NetworkOps[1] = &BombermanClientMgr::InstantiatePlayer;
		NetworkOps[2] = &BombermanClientMgr::KillOnlinePlayer;
		NetworkOps[3] = &BombermanClientMgr::InstantiateEgg;
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
		char password[] = { '0','4','5','1'}; //password 
		auto SerialTransform = LocalPlayer->transform.Serialize();

		int SendToServerSize = 4+SerialTransform->length;
		unsigned char* SendToServer = static_cast<unsigned char*>(malloc(SendToServerSize));
		if (SendToServer == nullptr)
		{
			std::cout << "ALLOCATION FAILED" << std::endl;
			exit(-1);
		}
		byteconverter::BytesAppend(SendToServer,SendToServerSize,  0, (unsigned char*)password, 4);
		byteconverter::BytesAppend(SendToServer,SendToServerSize,  4, SerialTransform->data, SerialTransform->length);

		char serverResponse[8];

		int sent_bytes = -1;
		int received_bytes = -1;
		int server_size = sizeof(Server_addr);
		sent_bytes = sendto(Server_socket, (char*)SendToServer, SendToServerSize, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		free(SendToServer);
		while (received_bytes == -1)
		{
			received_bytes = recvfrom(Server_socket, serverResponse, 8, 0, (struct sockaddr*)&Server_addr, &server_size);
		}



		id = byteconverter::BytesToInt((unsigned char*)serverResponse, 0, false);
		MapIndex = byteconverter::BytesToInt((unsigned char*)serverResponse, 4, false);
		MapIndexReceived.Broadcast(MapIndex);
		

		printf(" MY PLAYER-ID = %i\n", id);
		SetSocketBlockingEnabled((int)Server_socket, false);
		//player.ID = id;
		//message = calloc(1, 50);
	}

	/// <summary>
	/// DEPRECATED Send a series of bytes to the IP Server_Socket
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int BombermanClientMgr::OLD_SendToServer(unsigned char* data)
	{
		
		int sent_bytes = sendto(Server_socket, (char*)data, 50, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		if (sent_bytes < 0)
		{
			puts("Send failed");
			return -1;
		}
		return 0;

	}
	
	
	/// <summary>
	/// Send to the server all the queued data inside PacketBuffer
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int BombermanClientMgr::SendQueueToServer()
	{
		size_t l = PacketBuffer.size();
		unsigned char* data =(unsigned char*) calloc(1, l);
		if (data == nullptr)
		{
			return -1;
		}
		for (size_t i = 0; i < l; ++i)
		{
			data[i] = PacketBuffer.front();
			PacketBuffer.pop();
			
		}
		int sent_bytes = sendto(Server_socket, (char*)data, (unsigned int)l, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		free(data);
		
		if (sent_bytes < 0)
		{
			puts("Send failed");
			return -1;
		}
		return 0;

	}
	unsigned long BombermanClientMgr::GetIncomingPacketNumber()
	{
		unsigned long msg_length;
		int error = ioctlsocket(Server_socket, FIONREAD, &msg_length);

		return msg_length;
	}
	int  BombermanClientMgr::ReceiveFromServer(unsigned char* buffer, int buffer_length)
	{
		int server_size = sizeof(Server_addr);
		return recvfrom(Server_socket, (char*)buffer, buffer_length, 0, (struct sockaddr*)&(Server_addr), &server_size);
	}
	int  BombermanClientMgr::ProcessMessage(const unsigned char* message, const int msg_length)
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
	void BombermanClientMgr::Update()
	{

		secondAccumulator += BombermanTime::DeltaTime;
		if (secondAccumulator > NETWORK_PERIOD)
		{
			secondAccumulator = 0;
			//serialize local player
			std::cout << "GETTING TRANSFORM" << std::endl;

			float x = LocalPlayer->transform.GetPosition().x;
			
			if (x > 100)
			{
			std::cout << x << std::endl;
			std::cout << std::endl;

			}
			auto serializedTransform = LocalPlayer->GetPacketTransform();
			for (int i = 0; i < serializedTransform->length; ++i)
			{
				printf("|%X", serializedTransform->data[i]);
			}
			std::cout << std::endl;
			EnqueuePacket(serializedTransform->data, serializedTransform->length);
			
			//serialized_transform = .data;
			//memcpy(message, Network_ID, sizeof(int));
			//byteconverter::BytesAppend(message, 50, 4, command, sizeof(int));
			//byteconverter::BytesAppend(message, 50, 8, buffer_x, sizeof(float));
			//byteconverter::BytesAppend(message, 50, 12, buffer_y, sizeof(float));

			
			SendQueueToServer();

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
			BombermanClientMgr::ProcessMessage(message, n);
		}
	}
	void BombermanClientMgr::InstantiateEgg(const unsigned char* message, int playerID)
	{
		float X, Y;
		X = byteconverter::BytesToFloat(message, 8, true);
		Y = byteconverter::BytesToFloat(message, 12, true);
		auto new_egg = std::make_unique<Eggbomb*>(new Eggbomb(X, Y));
	}
	void BombermanClientMgr::InstantiatePlayer(const unsigned char* message, int playerID)
	{
		OnlinePlayer* newPlayer = new OnlinePlayer(playerID);

		OnlinePlayers[newPlayer->ID - 1] = newPlayer;
	}
	void BombermanClientMgr::UpdateOnlinePlayer(const unsigned char* message, int playerID)
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
	void BombermanClientMgr::KillOnlinePlayer(const unsigned char* message, int playerID)
	{
		OnlinePlayer* playerSelected = OnlinePlayers[playerID - 1];
		OnlinePlayers[playerID - 1] = NULL;
		UpdateMgr::RemoveItem(playerSelected);
	}
	void BombermanClientMgr::SendEggRequest(const Vector2 pos)
	{
		unsigned char* bufferX = byteconverter::FloatToBytes(pos.x);
		unsigned char* bufferY = byteconverter::FloatToBytes(pos.y);
		unsigned char* Network_ID = byteconverter::IntToBytes(id);
		unsigned char* command = byteconverter::IntToBytes(3);

		unsigned char msg[16];
		memcpy(msg, Network_ID, sizeof(int));
		byteconverter::BytesAppend(msg,16,4, command, sizeof(int));
		byteconverter::BytesAppend(msg,16,8, bufferX, sizeof(float));
		byteconverter::BytesAppend(msg,16,12, bufferY, sizeof(float));
		EnqueuePacket(msg, 16);
	}
	void BombermanClientMgr::EnqueuePacket(unsigned char* data, int bytesToInsert)
	{

		for (int i = 0; i < bytesToInsert; i++)
		{
			PacketBuffer.push(data[i]);

		}
		//SEPARATOR IS '|'
		PacketBuffer.push('|');


	}
};
