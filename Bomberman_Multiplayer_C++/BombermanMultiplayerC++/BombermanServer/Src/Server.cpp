#include "Server.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "LocalMap.h"
#include "Player.h"


//#include "NETMap.h"
#include "NETPhysicsMgr.h"
namespace Bomberman
{

	int							Server::currentMap;
	SOCKET						Server::ServerSocket;
	sockaddr_in					Server::IncomingClient;
	sockaddr_in					Server::ServerAddress;
	WSADATA						Server::wsa;
	std::vector<std::string>	Server::MapNames;
	 std::unordered_map<int, Server::NetworkCommandGenericServer>	Server::ServerNETCOMMANDS;


	int							Server::maxPacketSize;
	std::vector<unsigned char>	Server::message;
	std::map<unsigned int,std::shared_ptr<ActorData>>		Server::ObjectsToSync;
	std::map<ActorData*,unsigned int>		Server::ActorToID;

	//client lists:
	//
	std::map<unsigned int, std::shared_ptr<PlayerData>> Server::knownClients;
	//std::vector<pollfd>			Server::ExistingConnections;
	std::unordered_set<unsigned int> Server::blacklistedClients;



	void Server::Initialize(std::string address, int port,int mapIndex, int max_packet_size)
	{
		MapNames.push_back("..\\BombermanCore\\Include\\Maps\\map0.txt");

#pragma region SocketInit
		// Initialize Winsock dynamic library, this allows the usage of sockets.
		std::cout << "\nInitializing SERVER Winsock..." << std::endl;
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
			exit(-1);
		}
		std::cout << "Socket created" << std::endl;

		int test = 1;
		int rc = setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&test, sizeof(test));
		//Prepare the sockaddr_in structure
		memset(&ServerAddress, 0, sizeof(ServerAddress));
		ServerAddress.sin_family = AF_INET;
		ServerAddress.sin_port = htons(port);
		inet_pton(AF_INET, address.c_str(), &ServerAddress.sin_addr);
		if (ServerAddress.sin_addr.S_un.S_addr == INADDR_LOOPBACK)
		{
			//int rc = setsockopt(ServerSocket, SOL_SOCKET, SO_USELOOPBACK, (char*)&test, sizeof(test));
			//ServerAddress.sin_addr.S_un.S_addr = INADDR_ANY;
			std::cout << "SERVER EXISTS ON THE SAME MACHINE \n";
		}

		// Connect to server

		if (bind(ServerSocket, (sockaddr*) & ServerAddress, sizeof(ServerAddress)) < 0)
		{
			printf("Bind failed with error code : %d", WSAGetLastError());
			exit(-1);
		}
		std::cout << "Server succesfully created with socket => " <<
			(int)ServerAddress.sin_addr.S_un.S_un_b.s_b1 << "."<<
			(int)ServerAddress.sin_addr.S_un.S_un_b.s_b2 <<	"."<<
			(int)ServerAddress.sin_addr.S_un.S_un_b.s_b3 <<	"."<<
			(int)ServerAddress.sin_addr.S_un.S_un_b.s_b4 << "."<<
			":" << ServerAddress.sin_port << "\n";

		//set non blocking
		SetSocketBlockingEnabled((int)ServerSocket, false);
#pragma endregion


		//init pollfd struct
		//ExistingConnections = std::vector<pollfd>(1);
		//ExistingConnections[0].fd = ServerSocket;
		//ExistingConnections[0].events = POLLIN;
		

		currentMap = mapIndex;
		LoadMap(mapIndex);
		maxPacketSize = max_packet_size;

		ServerNETCOMMANDS = std::unordered_map<int, Server::NetworkCommandGenericServer>();
		ServerNETCOMMANDS.reserve((int)NETCOMMANDType::COUNT);
		ServerNETCOMMANDS[NETCOMMANDType::PlayerInput] = &Server::ReceiveInput;

		message.reserve(MAX_PACKET_SIZE);
		message.resize(message.capacity());

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
	
		while (true)
		{
			try
			{
				BombermanTime::DeltaTimeUpdate();
				NETPhysicsMgr::Update();
				NETPhysicsMgr::CheckCollisions();
				CheckClientStatus();
				
				//if (WSAPoll((pollfd*) & ExistingConnections[0], (unsigned int)ExistingConnections.size(), 100) <= 0)
				//	continue;
				//if (ExistingConnections[0].fd == ServerSocket)
				//{
				//
				//}
				int sizeClient = sizeof(IncomingClient);
				for (int i = 0; i < 100; ++i)
				{
					unsigned long msgLength = 0;
					int error = ioctlsocket(ServerSocket, FIONREAD, &msgLength);
					if (msgLength <= 0)
					{
						break;
					}
					message.resize(msgLength);
					int bytesReceived = recvfrom(ServerSocket, (char*)message.data(), MAX_PACKET_SIZE, 0, (sockaddr*)&(IncomingClient), &sizeClient);
					if (bytesReceived == -1)
					{
						break;
					}

				//std::system("cls");
				//std::cout << "MSG LENGTH : " << bytesReceived << "\n" << std::endl;
				//for (int i = 0; i < bytesReceived; ++i)
				//{
				//	if (i % 4 == 0)
				//	{
				//		std::cout << "\n";
				//	}
				//	std::cout << std::hex << (int)message[i] << "|";
				//}

				//std::cout << "\n" << std::dec;
				//std::cout << IncomingClient.sin_addr.S_un.S_addr << std::endl;
				bool one = IsClientBlacklisted(IncomingClient);
				bool two = IsClientKnown(IncomingClient);
			
				if (one == false )
				{
					if (two == false)
					{
						if (CheckClientPassword(IncomingClient))
						{
							AcceptClient(IncomingClient);
							
						}
						else
						{
							BlacklistClient(IncomingClient);
						}
							continue;

					}
				}
				else
				{
					continue;
				}
				
				

				std::shared_ptr<std::vector<NetworkPacket>> msg = NetworkPacket::Unpack(&message, false);
				ProcessMessage(IncomingClient,msg,bytesReceived);
				
				SendWorldStatus(IncomingClient);
				message.assign(message.size(), 0);
				
				
				}
			}
			catch (const std::exception&)
			{
				std::cout << "TIMED OUT" << std::endl;
			}
		}
	}

	bool Server::IsClientKnown(sockaddr_in client)
	{
		unsigned int key = static_cast<unsigned int>(client.sin_addr.S_un.S_addr);
	
		return knownClients.count(key);
		
	}
	bool Server::CheckClientPassword(sockaddr_in client)
	{
		auto key = static_cast<unsigned int>(client.sin_addr.S_un.S_addr);

		std::cout << "UNKNOWN CLIENT" << std::endl;

		std::string correctPassword = "0451";//30 34 35 31
		std::string recvPassword =
		{
			(char)message.data()[0],
			(char)message.data()[1],
			(char)message.data()[2],
			(char)message.data()[3]
		};

		if (correctPassword.compare(recvPassword) == 0)
		{
			std::cout << "PASSWORD CORRECT, NEW CLIENT ACCEPTED" << std::endl;
			return true;
		}
		else
		{
			std::cout << "PASSWORD INCORRECT, CLIENT BLACKLISTED" << std::endl;
			return false;
		}
		
	}
	int Server::LoadMap(int MapIndex)
	{
		std::ifstream my_file;
		my_file.open(MapNames[MapIndex]);
		std::string current_line;
		int iterations = 0;

		while (std::getline(my_file, current_line))
		{
			if (current_line.empty() == true ||
				current_line == " " ||
				(current_line[0] == '/' &&
					current_line[1] == '/'))
				continue;
			int x, y, w, h;
			bool isStatic;
			//size_t current_index,next_index;

			std::vector<std::string> splitted = ByteConverter::split(current_line, ',');
			x = stoi(splitted[0]);
			y = stoi(splitted[1]);
			w = stoi(splitted[2]);
			h = stoi(splitted[3]);
			stoi(splitted[4]) > 0 ? isStatic = true : isStatic = false;



			auto NewTile = std::make_shared<Tile>(x,y,w,h,isStatic);
			
			auto TileData = std::make_shared<ActorData>(NewTile->transform);

			ObjectsToSync[iterations] = TileData;
			//new_tile.get()->position = { x,y,w,h };
			//ObjectsToSync.push_back({ x,y,w,h }, isStatic);
			iterations++;

		}
		my_file.close();
		//std::cout << debug_int << std::endl;
		return MapIndex;
		//std::list<SDL_Rect> list_to_add;

	
	}
	
	void Server::CheckClientStatus()
	{
		time_t now;
		std::time(&now);

		return;

		
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
	
	void Server::ProcessMessage(sockaddr_in incoming,const std::shared_ptr<std::vector<NetworkPacket>> message,int length)
	{
		
		std::shared_ptr<PlayerData> actorInQuestion = knownClients[(unsigned int)incoming.sin_addr.S_un.S_addr];
		actorInQuestion->LastPacketDate = std::time(0);
		
		int remainingBytes = length;
		for (auto i =  message->begin();i != message->end();++i)
		{
			NetworkPacket currentCommand = (*i);
			if (remainingBytes > 0)
			{
				NetworkCommandGenericServer toCall = ServerNETCOMMANDS[currentCommand.CommandType];
				if (toCall != nullptr)
				{
					
					remainingBytes-=(*toCall)(incoming, currentCommand);

				}

			}

		}
		
	}

	void Server::BlacklistClient(sockaddr_in toBlacklist)
	{
		unsigned int converted = static_cast<unsigned int>(toBlacklist.sin_addr.S_un.S_addr);
		blacklistedClients.insert(converted);
		std::cout << "CLIENT WAS BLACKLISTED" << std::endl;
	}

	void Server::AcceptClient(sockaddr_in s)
	{
		float x, y, w, h; // default player position and dimension
		//Vector2 pos = DEFAULT_POS;

		//Vector2 dim = DEFAULT_DIM;
		
		w = 64;
		h = 64;
		unsigned int key = static_cast<unsigned int>(s.sin_addr.S_un.S_addr);
		int ID =(int)ObjectsToSync.size();

		std::shared_ptr<std::vector<unsigned char>> Welcome = std::make_shared<std::vector<unsigned char>>(4*6);
		ByteConverter::BytesAppend(Welcome, 0, ByteConverter::IntToBytes(ID),4);
		ByteConverter::BytesAppend(Welcome, 4, ByteConverter::IntToBytes(currentMap),4);
		ByteConverter::BytesAppend(Welcome, 8, ByteConverter::FloatToBytes(DEFAULT_POS.x),4);
		ByteConverter::BytesAppend(Welcome, 12,ByteConverter::FloatToBytes(DEFAULT_POS.y),4);
		ByteConverter::BytesAppend(Welcome, 16,ByteConverter::FloatToBytes(DEFAULT_DIM.x),4);
		ByteConverter::BytesAppend(Welcome, 20,ByteConverter::FloatToBytes(DEFAULT_DIM.y),4);

		
		// TODO: ID + MAP_ID + COLLIDER
		sendto(ServerSocket, (char*)Welcome->data(), 4 * 6, 0, (struct sockaddr*)&s, sizeof(s));

		//std::shared_ptr<Transform> receivedTransform = std::make_shared<Transform>( reinterpret_cast<Transform*>(ISerializable::Deserialize(std::make_shared<SerialData>(ser))));
	
		auto newActor = std::make_shared<PlayerData>(x, y, w, h);

		knownClients.insert({ key,newActor });
		
		ObjectsToSync[ID] = newActor;
		ActorToID[newActor.get()] = ID;
		//NETPhysicsMgr::AddItem(newActor->rigidbody);
		
	}
	bool Server::IsClientBlacklisted(sockaddr_in s)
	{
		auto key = static_cast<unsigned int>(s.sin_addr.S_un.S_addr);
		return blacklistedClients.contains(key);
		//return  blacklistedClients.find(key)._Ptr != nullptr;
	}
	void Server::SendWorldStatus(sockaddr_in client)
	{
		
		//clear msg
		message.assign(message.size(), 0);
		
		unsigned int target = 0,iterations =0;
		
		for (auto i = ObjectsToSync.begin(); i != ObjectsToSync.end(); ++i)
		{
			int currentID = (*i).first;
			/*if (currentID == 0x1c)
			{
				std::cout << "Stop";
			}*/
			
			std::shared_ptr<SerialData> transform = (*i).second->GetPacketTransform();
			
			//set command 
			int size = 0;
			ByteConverter::BytesAppend(&message, target, ByteConverter::IntToBytes((int)NETCOMMANDType::Update).get(), 4);
			target += sizeof(int);
			size += 4;
			// set ID of transform to update
			ByteConverter::BytesAppend(&message, target, ByteConverter::IntToBytes(currentID).get(), 4);
			target += sizeof(int);
			size += 4;
			//data length
		
			size += transform->data->size();
			size += 4;
			int corroborateSize = 12 + transform->data->size();
			ByteConverter::BytesAppend(&message, target, ByteConverter::IntToBytes(size).get(), 4);
			target += sizeof(int);
			//set data
			ByteConverter::BytesAppend(&message, target, transform->data,transform->data->size());
			target += transform->data->size();
			++iterations;
		}
		int size = sizeof(client);
		sendto(ServerSocket, (char*)message.data(), MAX_PACKET_SIZE, 0, (sockaddr*)&client, size);
	}
	int Server::ReceiveInput(sockaddr_in client,const NetworkPacket msg)
	{
		std::shared_ptr<PlayerData> p = knownClients[client.sin_addr.S_un.S_addr];
		PlayerInputType ID = static_cast<PlayerInputType>(ByteConverter::BytesToInt(msg.Payload->data, 4));
		switch (ID)
		{
			case Movement:
			{
				int ID = ActorToID.at(p.get());
				float x = ByteConverter::BytesToFloat(msg.Payload->data->data(), 8, false);
				float y = ByteConverter::BytesToFloat(msg.Payload->data->data(), 12, false);
				Vector2 newVel = Vector2(x, y);
				if (ID == 0x1c)
				{
					std::cout << "Server X: "<<x <<"\n";
					std::cout << "Server Y: " << y<< "\n";

				}
				float test = newVel.Magnitude();
				if ( test > 1 )
				{
					newVel = Vector2(x, y);
					//std::cout << "STOP. VELOCITY CHECK";
				}
				p->rigidbody->velocity = newVel;
				break;

			}
			case EggRequest:
			{

				break;
			}

		}
		return 16;
	}
}