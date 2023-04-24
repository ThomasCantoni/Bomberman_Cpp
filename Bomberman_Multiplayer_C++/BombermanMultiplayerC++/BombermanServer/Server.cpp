#include "Server.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

#include "Map.h"
#include "PhysicsMgr.h"
namespace Bomberman
{

	int							Server::currentMap;
	SOCKET						Server::ServerSocket;
	sockaddr_in					Server::IncomingClient;
	sockaddr_in					Server::ServerAddress;
	WSADATA						Server::wsa;
	std::vector<std::string>	Server::MapNames;


	int							Server::maxPacketSize;
	unsigned char				Server::message[256];
	std::vector<std::shared_ptr<ActorData>>		Server::ObjectsToSync;
	//client lists:
	//
	std::map<unsigned int, std::shared_ptr<PlayerData>> Server::knownClients;
	//std::vector<pollfd>			Server::ExistingConnections;
	std::unordered_set<unsigned int> Server::blacklistedClients;



	void Server::Initialize(std::string address, int port,int mapIndex, int max_packet_size)
	{
		MapNames.push_back("..\\BombermanCore\\Include\\Maps\\map1.txt");

		// Initialize Winsock dynamic library, this allows the usage of sockets.
		std::cout << "\nInitializing Winsock..." << std::endl;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("Failed. Error Code : %d", WSAGetLastError());
			exit(-1);
		}
		std::cout << "Initialized" << std::endl;


		// Create a socket
		ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (ServerSocket < 0)
		{
			printf("Could not create socket : %d", WSAGetLastError());
		}
		std::cout << "Socket created" << std::endl;

		int test = 1;
		int rc = setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR,	(char*)&test, sizeof(test));

		//Prepare the sockaddr_in structure
		memset(&ServerAddress, 0, sizeof(ServerAddress));
		ServerAddress.sin_family = AF_INET;
		ServerAddress.sin_port = htons(port);
		inet_pton(AF_INET, address.c_str(), &ServerAddress.sin_addr);

		// Connect to server
		
		if (bind(ServerSocket, (const struct sockaddr*)&ServerAddress, sizeof(struct sockaddr_in)) != 0)
		{
		    printf("Bind failed with error code : %d", WSAGetLastError());
		    exit(-1);
		}
		printf("Server succesfully created.\n");

		//set non blocking
		SetSocketBlockingEnabled((int)ServerSocket, false);

		//init pollfd struct
		//ExistingConnections = std::vector<pollfd>(1);
		//ExistingConnections[0].fd = ServerSocket;
		//ExistingConnections[0].events = POLLIN;
		

		currentMap = mapIndex;
		LoadMap(currentMap);
		maxPacketSize = max_packet_size;
		
	}
	int Server::SetMap(int MapIndex)
	{
		currentMap = MapIndex;
		//TO DO
		// tell all players to change map
		return MapIndex;
	}
	void Server::Run()
	{
		int clientsize = sizeof(IncomingClient);
		while (true)
		{
			try
			{
				CheckStatus();
				//std::cout << "LISTENING" << std::endl;
				//if (WSAPoll((pollfd*) & ExistingConnections[0], (unsigned int)ExistingConnections.size(), 100) <= 0)
				//	continue;
				//if (ExistingConnections[0].fd == ServerSocket)
				//{
				//
				//}
				
				int bytesReceived = recvfrom(ServerSocket, (char*)message, MAX_PACKET_SIZE, 0, (sockaddr*)&(IncomingClient), &clientsize);
				if (bytesReceived == -1)
				{
					continue;
				}
				//std::cout << IncomingClient.sin_addr.S_un.S_addr << std::endl;
				if (CheckClient(IncomingClient) == false)
				{	
					//if client is invalid or blacklisted
					continue;
				}
				
				
				ProcessMessage(IncomingClient);
				//PhysicsMgr::Update();
				//PhysicsMgr::CheckCollisions();
				memset(message, 0, MAX_PACKET_SIZE);
			}
			catch (const std::exception&)
			{
				std::cout << "TIMED OUT" << std::endl;
			}
		}
	}
	bool Server::CheckClient(sockaddr_in client)
	{
		auto key = static_cast<unsigned int>(client.sin_addr.S_un.S_addr);

		bool actorValid = CheckIfBlacklisted(key);
		bool actorKnown = knownClients.count(key) == 1 ? true : false;
		if (actorValid == false)
		{
			BlacklistClient(key);
			return false;
		}
		if (actorKnown==false)
		{
			std::cout << "UNKNOWN CLIENT" << std::endl;

			std::string compare = "0451";//30 34 35 31
			std::string recv_password =
			{
				(char)message[0],
				(char)message[1],
				(char)message[2],
				(char)message[3]
			};

			if (compare.compare(recv_password) == 0)
			{
				std::cout << "PASSWORD CORRECT, NEW CLIENT ACCEPTED" << std::endl;
				AcceptClient(IncomingClient);
				return true;
			}
			else
			{
				std::cout << "PASSWORD INCORRECT, CLIENT BLACKLISTED" << std::endl;
				BlacklistClient(key);
				return false;
			}
		}
		return actorKnown && actorValid;
	}
	int Server::LoadMap(int MapIndex)
	{
		std::ifstream my_file;
		my_file.open(MapNames[MapIndex]);
		std::string current_line;
		int debug_int = 0;

		while (std::getline(my_file, current_line))
		{
			if (current_line.empty() == true)
				continue;
			int x, y, w, h;
			bool isStatic;
			//size_t current_index,next_index;

			std::vector<std::string> splitted = byteconverter::split(current_line, ',');
			x = stoi(splitted[0]);
			y = stoi(splitted[1]);
			w = stoi(splitted[2]);
			h = stoi(splitted[3]);
			stoi(splitted[4]) > 0 ? isStatic = true : isStatic = false;



			auto NewTile = std::make_shared<Tile>(x,y,w,h,isStatic);
			
			auto TileData = std::make_shared<ActorData>(NewTile.get()->transform);

			ObjectsToSync.push_back(TileData);
			//new_tile.get()->position = { x,y,w,h };
			//ObjectsToSync.push_back({ x,y,w,h }, isStatic);
			debug_int++;

		}
		my_file.close();
		std::cout << debug_int << std::endl;
		return MapIndex;
	}
	
	void Server::CheckStatus()
	{
		time_t now;
		std::time(&now);

		

		
		for (auto iter= knownClients.begin(); iter!= knownClients.end();)
		{
			if (now - (*iter).second->LastPacketDate > 5)
			{
				//forget client
				knownClients.erase(iter++);
				std::cout << "CLIENT DIED" << std::endl;
			}
			else
			{
				++iter;
			}
		}
		
	}
	
	void Server::ProcessMessage(sockaddr_in incoming)
	{
		auto actorInQuestion = knownClients[(unsigned int)incoming.sin_addr.S_un.S_addr];
		actorInQuestion->LastPacketDate = std::time(0);

		if (ObjectsToSync.size() > 0)
		{

		}
	}

	void Server::BlacklistClient(unsigned int toBlacklist)
	{
		blacklistedClients.insert(toBlacklist);
		std::cout << "CLIENT WAS BLACKLISTED" << std::endl;
	}

	void Server::AcceptClient(sockaddr_in s)
	{
		unsigned int key = static_cast<unsigned int>(s.sin_addr.S_un.S_addr);
		unsigned char Welcome[24];
		int ID =(int)knownClients.size();
		byteconverter::BytesAppend(Welcome,24, 0, byteconverter::IntToBytes(ID),4);
		byteconverter::BytesAppend(Welcome,24, 4, byteconverter::IntToBytes(currentMap),4);
		
		sendto(ServerSocket, (char*)Welcome, 8, 0, (struct sockaddr*)&s, sizeof(s));
		
		
		unsigned char* pos_x =byteconverter::BytesCopy(message, 20, 4,	 4);
		unsigned char* pos_y =byteconverter::BytesCopy(message, 20, 8,	 4);
		unsigned char* dim_x =byteconverter::BytesCopy(message, 20, 12, 4);
		unsigned char* dim_y =byteconverter::BytesCopy(message, 20, 16, 4);

		float x, y, w, h;
		x = byteconverter::BytesToFloat(pos_x, 0,false);
		y = byteconverter::BytesToFloat(pos_y, 0,false);
		w = byteconverter::BytesToFloat(dim_x, 0,false);
		h = byteconverter::BytesToFloat(dim_y, 0,false);

		auto newActor = std::make_shared<PlayerData>(x, y, w, h);
		
		knownClients[key] =  newActor;
		
	}
	bool Server::CheckIfBlacklisted(unsigned int key)
	{
		auto i = blacklistedClients.find(key);
		return  i == blacklistedClients.end() ? true : false;
	}
	void Server::SendWorldStatus(sockaddr_in client)
	{
		//clear msg
		memset(message, 0, sizeof(message));
		unsigned int target = 0,iterations =0;
		
		for (auto i = ObjectsToSync.begin(); i != ObjectsToSync.end(); ++i)
		{
			auto transform = (*i)->GetPacketTransform();
			
			//set command 
			byteconverter::BytesAppend(message,MAX_PACKET_SIZE, target, (int)NetCommand::UpdateMapStatus);
			target += sizeof(int);
			// set ID of tile
			byteconverter::BytesAppend(message, MAX_PACKET_SIZE, target, (int)iterations); 
			target += sizeof(int);
			//set data
			byteconverter::BytesAppend(message,MAX_PACKET_SIZE, target,transform->data,transform->length);
			++iterations;
			target += transform->length;
		}
		int size = sizeof(client);
		sendto(ServerSocket, (char*)message, MAX_PACKET_SIZE, 0, (sockaddr*)&client, size);
	}
}