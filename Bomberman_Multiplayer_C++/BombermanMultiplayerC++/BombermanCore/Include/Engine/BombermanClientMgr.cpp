#pragma once
#include "BombermanClientMgr.h"
#include "Player.h"
#include "Vector2.h"
//#include "Map.h"

namespace Bomberman
{


	SOCKET						BombermanClientMgr::Server_socket;
	sockaddr_in					BombermanClientMgr::Server_addr;
	WSADATA						BombermanClientMgr::wsa;

	int							BombermanClientMgr::MapIndex;
	
	std::vector<unsigned char>		BombermanClientMgr::message;
	float						BombermanClientMgr::secondAccumulator;

	//std::vector<OnlinePlayer*>  BombermanClientMgr::OnlinePlayers;
	std::unordered_map<int,Transform*>		BombermanClientMgr::TransformsToSync;
	std::unordered_map<int, OnlinePlayer*>		BombermanClientMgr::OnlinePlayers;


	//std::unordered_map<int, BombermanClientMgr::NetworkCommandGeneric>	BombermanClientMgr::NETCOM_Actors;
	//std::unordered_map<int, BombermanClientMgr::NetworkCommandLocalPlayer>	BombermanClientMgr::NETCOM_LocalPlayer;
	std::unordered_map<int, BombermanClientMgr::NetworkCommandGeneric>	BombermanClientMgr::NETCOMMANDS;
	std::queue<unsigned char>	BombermanClientMgr::PacketBuffer;

	MulticastDelegate<int,int,Vector2,Vector2> BombermanClientMgr::ServerConnectionEstablished;


	unsigned char* BombermanClientMgr::Initialize(const char* server_ip, const int port)
	{

		NETCOMMANDS = std::unordered_map<int, BombermanClientMgr::NetworkCommandGeneric>();
		NETCOMMANDS.reserve((int)NETCOMMANDType::COUNT);
		NETCOMMANDS[NETCOMMANDType::Update]		=	&BombermanClientMgr::UpdateOnlinePlayer;
		NETCOMMANDS[NETCOMMANDType::Announce]	=	&BombermanClientMgr::InstantiatePlayer;
		NETCOMMANDS[NETCOMMANDType::Death]		=	&BombermanClientMgr::KillOnlinePlayer;
		NETCOMMANDS[NETCOMMANDType::EggSpawn]	=	&BombermanClientMgr::InstantiateEgg;
		NETCOMMANDS[NETCOMMANDType::ChangeMap]	=	&BombermanClientMgr::Travel;


		#pragma region Connection

		// Initialize Winsock
		std::cout << "\nInitializing CLIENT Winsock...\n";
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			std::cout << "Failed. Error Code" << WSAGetLastError() << "\n";
			exit(-1);
		}

		// Create a socket
		Server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (Server_socket < 0)
		{
			std::cout << "Could not create socket :" << WSAGetLastError() << "\n";
			exit(-1);
		}
		
		int test = 1;
		//int rc = setsockopt(Server_socket, SOL_SOCKET, SO_REUSEADDR , (char*)&test, sizeof(test));
		// Prepare the sockaddr_in structure
		memset(&Server_addr, 0, sizeof(Server_addr));
		Server_addr.sin_family = AF_INET;
		Server_addr.sin_port = htons(port);
		inet_pton(AF_INET, server_ip, &Server_addr.sin_addr);
		//if (bind(Server_socket, (sockaddr*)&Server_addr, sizeof(Server_addr)) < 0)
		//{
		//	printf("Bind failed with error code : %d", WSAGetLastError());
		//	exit(-1);
		//}
		std::cout <<"Client socket succesfully created on " <<
			(int)Server_addr.sin_addr.S_un.S_un_b.s_b1 << "." <<
			(int)Server_addr.sin_addr.S_un.S_un_b.s_b2 << "." <<
			(int)Server_addr.sin_addr.S_un.S_un_b.s_b3 << "." <<
			(int)Server_addr.sin_addr.S_un.S_un_b.s_b4 << "." <<
			":" << Server_addr.sin_port << "\n";

		char password[] = { '0','4','5','1'}; //password 
		int sent_bytes = -1;
		int received_bytes = -1;
		int length = 4;
		std::cout << "Attempting to connect to server " << server_ip<< " with port "<<Server_addr.sin_port ;
		sent_bytes = sendto(Server_socket, (char*)password, length, 0, (struct sockaddr*)&Server_addr, sizeof(sockaddr_in));
		if (sent_bytes == -1)
		{
			std::cout << "SEND FAILED!!!!!!!\n";
		}


		char serverResponse[24] = {};
		int server_size = sizeof(Server_addr);
		received_bytes = recvfrom(Server_socket, serverResponse, 24, 0, (struct sockaddr*)&Server_addr, &server_size);



		
		int id	= byteconverter::BytesToInt((unsigned char*)serverResponse, 0,  false);
		int MapIndex	= byteconverter::BytesToInt((unsigned char*)serverResponse,  4,  false);
		float posX		= byteconverter::BytesToFloat((unsigned char*)serverResponse, 8,  false);
		float posY		= byteconverter::BytesToFloat((unsigned char*)serverResponse, 12, false);
		float dimX		= byteconverter::BytesToFloat((unsigned char*)serverResponse, 16, false);
		float dimY		= byteconverter::BytesToFloat((unsigned char*)serverResponse, 20, false);
		
		Vector2 position(posX, posY);
		Vector2 dimen(dimX, dimY);
		
		ServerConnectionEstablished.Broadcast(id, MapIndex,position,dimen);
		
		TransformsToSync[id] = &Player::GetLocalPlayer()->transform;

		//std::cout <<" MY PLAYER - ID = "<< id << " \n ";
		SetSocketBlockingEnabled((int)Server_socket, false);
#pragma endregion

		
		message.reserve(MAX_PACKET_SIZE);
		message.resize(message.capacity());
	}

	
	
	
	/// <summary>
	/// Send to the server all the queued data inside PacketBuffer
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int BombermanClientMgr::SendQueueToServer()
	{
		const size_t l = PacketBuffer.size();
		message.assign(message.size(), 0); //equal to writing memset(0)
		//message.resize(l);
		//unsigned char* data =static_cast<unsigned char*> (calloc(1, l));
		
		for (int i = 0; i < l; ++i)
		{
			message[i] =  PacketBuffer.front();
			
			PacketBuffer.pop();
			
		}
						 
		int sent_bytes = sendto(Server_socket, (char*)message.data(), (unsigned int)l, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		//std::cout << "SENDING TO SERVER : " << std::endl;
		//for (int i = 0; i < sent_bytes; ++i)
		//{
		//	if (i % 4 == 0)
		//	{
		//		std::cout << "\n";
		//	}
		//	std::cout << std::hex << (int)data[i] << "|";
		//}

		//std::cout <<"\n "<< std::dec;
		
		
		if (sent_bytes < 0)
		{
			puts("Send failed");
			return -1;
		}
	
		return 0;

	}
	unsigned long BombermanClientMgr::GetIncomingPacketNumber()
	{
		unsigned long msg_length=0;
		int error = ioctlsocket(Server_socket, FIONREAD, &msg_length);
		
		return msg_length;
	}
	int  BombermanClientMgr::ReceiveFromServer(std::vector<unsigned char>* buffer)
	{
		int server_size = sizeof(Server_addr);
		//unsigned char* data = &(buffer.data())[0];
		return recvfrom(Server_socket, (char*)message.data(), MAX_PACKET_SIZE, 0, (struct sockaddr*)&(Server_addr), &server_size);

		//return recvfrom(Server_socket, (char*)buffer->data(), MAX_PACKET_SIZE, 0, (struct sockaddr*)&(Server_addr), &server_size);
	}
	int  BombermanClientMgr::ProcessMessage(const std::vector<unsigned char> message, const int msgLength)
	{
		//std::shared_ptr<unsigned char> message2 = std::make_shared<unsigned char>(message);
		int BytesRemaining = msgLength;
		int currentIndex = 0;
		std::vector<std::shared_ptr<unsigned char[]>> messageSplitted = byteconverter::split(message, PACKET_DELIMITER);
		/*for (int i = 0; i < messageSplitted.size(); ++i)
		{
			unsigned char* Mess = messageSplitted.at(i).get();

			for (int j= 0; j < strlen((char*)Mess); ++j)
			{
				if (j % 4 == 0)
					std::cout << "\n";
				std::cout <<std::hex<<(int) Mess[j] << "|";
			}
			std::cout << "\n\n";

		}*/
		for (int i=0;i< messageSplitted.size();++i)
		{
			auto Mess = messageSplitted.at(i).get();
			NETCOMMANDType commandCode = static_cast<NETCOMMANDType>(byteconverter::BytesToInt(Mess, 0,false));
			//std::cout << "RECEIVED COMMAND " << commandCode << "\n";
			int player_id = byteconverter::BytesToInt(Mess, 4,false);
			//std::cout << "RECEIVED PLAYERID "<< player_id <<"\n";

			NetworkCommandGeneric methodToCall = NETCOMMANDS[commandCode];
			if (methodToCall != nullptr)
			{
				
				int bytesUsed = (*methodToCall)(Mess);
				BytesRemaining -= bytesUsed;
				currentIndex += bytesUsed;
			}
			else
			{
				std::cout << "COMMAND RECEIVED INVALID!!!!! \n";
			}
		
		}
		
		return 0;
	}
	void BombermanClientMgr::Update()
	{

		secondAccumulator += BombermanTime::DeltaTime;
		if (secondAccumulator > NETWORK_PERIOD)
		{
			secondAccumulator = 0;

			auto velocityData = Player::GetLocalPlayer()->GetPacketMovement();
			if (Player::GetLocalPlayer()->velocity.Magnitude() > 0)
			{
				std::cout << "";
			}
			EnqueuePacket(velocityData->data, 16);
			SendQueueToServer();

		}
		// get info from server
		for (int i = 0; i < 500; ++i)
		{


			unsigned long msgLength = GetIncomingPacketNumber();
			if (msgLength == 0)
				return;
			message.assign(message.size(), 0); //clear the occupied slots
			message.resize(msgLength); //this is not as heavy as doing a realloc because the 1024 slots have already been reserved,
			//the resize doesn't have to allocate
			int n = ReceiveFromServer(&message);
			std::vector<std::shared_ptr<unsigned char[]>> messageSplitted = byteconverter::split(message, PACKET_DELIMITER);


			//unsigned char* message2 = (unsigned char*)malloc(msgLength);
			//int server_size = sizeof(Server_addr);
			// n =recvfrom(Server_socket, (char*)message2,msgLength, 0, (struct sockaddr*)&(Server_addr), &server_size);
			// std::vector<std::shared_ptr<unsigned char[]>> messageSplitted2 = byteconverter::split(message2, msgLength, PACKET_DELIMITER);
		   
			if (n <= 0)
				return;
			//printf("Received %d bytesfrom %s : %d : %.*s \n", n, inet_ntop(NM->Server_addr.sin_addr), ntohs(NM->Server_addr.sin_port), n, message);
			BombermanClientMgr::ProcessMessage(message, n);

		}
		message.clear();
	}
	int BombermanClientMgr::InstantiateEgg(const unsigned char* message)
	{
		float X, Y;
		X = byteconverter::BytesToFloat(message, 8, true);
		Y = byteconverter::BytesToFloat(message, 12, true);
		auto new_egg = std::make_unique<Eggbomb*>(new Eggbomb(X, Y));
		return 0;
	}
	int BombermanClientMgr::InstantiatePlayer(const unsigned char* message)
	{

		//OnlinePlayer* newPlayer = new OnlinePlayer(PlayerID);
		//
		//OnlinePlayers[newPlayer->ID - 1] = newPlayer;
		return 0;
	}
	int BombermanClientMgr::UpdateOnlinePlayer(const unsigned char* message)
	{
		int id = byteconverter::BytesToInt(message, 4,false);
		float printX, printY;
		if (strlen((char*)message) + 12+3 >= MAX_PACKET_SIZE)
		{
			std::cout <<"";
		}
		printX = byteconverter::BytesToFloat(message, 8,false);
		printY = byteconverter::BytesToFloat(message, 12, false);
		int playerID = Player::GetLocalPlayer()->ID;
		if (playerID == id)
		{
			if (printX > 0)
			{
				std::cout << "";
			}
			Player::GetLocalPlayer()->transform.SetPosition(printX, printY);
			return 4;
		}
		Transform* toUpdate = TransformsToSync[id];
		if(toUpdate != nullptr)
			toUpdate->SetPosition(printX, printY);
		return 4;
		OnlinePlayer* playerSelected = OnlinePlayers[id - 1];
		
		
		playerSelected->old_position.x = playerSelected->latest_position.x;
		playerSelected->old_position.y = playerSelected->latest_position.y;
		playerSelected->latest_position.x = printX;
		playerSelected->latest_position.y = printY;
		playerSelected->lerp_accumulator = 0;
		std::cout << "#################################################" << std::endl;
		std::cout << "UPDATE PLAYER" << std::endl;
		std::cout << "Player ID = " << Player::GetLocalPlayer()->ID << std::endl;
		std::cout << "POSITIONS : " << printX << " " << printY << std::endl;
		std::cout << "#################################################" << std::endl;
	}
	int BombermanClientMgr::KillOnlinePlayer(const unsigned char* message	)
	{

		//OnlinePlayer* playerSelected = OnlinePlayers[playerID - 1];
		//OnlinePlayers[playerID - 1] = NULL;
		//UpdateMgr::RemoveItem(playerSelected);
		return 0;
	}
	int BombermanClientMgr::Travel(const unsigned char* data)
	{
		return 0;
	}


	void BombermanClientMgr::SendEggRequest(const Vector2 pos)
	{
		//unsigned char* bufferX = byteconverter::FloatToBytes(pos.x);
		//unsigned char* bufferY = byteconverter::FloatToBytes(pos.y);
		//unsigned char* Network_ID = byteconverter::IntToBytes(id);
		//unsigned char* command = byteconverter::IntToBytes(3);
		//
		//unsigned char msg[16];
		//memcpy(msg, Network_ID, sizeof(int));
		//byteconverter::BytesAppend(msg,16,4, command, sizeof(int));
		//byteconverter::BytesAppend(msg,16,8, bufferX, sizeof(float));
		//byteconverter::BytesAppend(msg,16,12, bufferY, sizeof(float));
		//EnqueuePacket(msg, 16);
		
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
	void BombermanClientMgr::EnqueuePacket(std::shared_ptr<unsigned char> data, int bytesToInsert)
	{

		for (int i = 0; i < bytesToInsert; i++)
		{
			PacketBuffer.push(data.get()[i]);

		}
		//SEPARATOR IS '|'
		PacketBuffer.push('|');


	}
};
