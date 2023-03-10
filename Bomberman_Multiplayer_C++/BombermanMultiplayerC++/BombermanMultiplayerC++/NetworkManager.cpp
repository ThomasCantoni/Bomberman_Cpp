#pragma once
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>

#include "byteconverter.cpp"
#include <string>
class NetworkManager
{
public:
	SOCKET Server_socket;
	
	sockaddr_in Server_addr;
	WSADATA wsa;
	int id;
	//int send_to_server(unsigned char* data);
	//NetworkManager(char* ip, unsigned int port);
	int set_nb(int s)
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


	NetworkManager(const char* server_ip,const int port)
	{
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
		int sent_bytes = sendto(Server_socket, data, 4, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		int server_size = sizeof(Server_addr);
		sent_bytes = recvfrom(Server_socket, data, 4, 0, (struct sockaddr*)&Server_addr, &server_size);

		 id = byteconverter::BytesToInt(data);

		printf(" MY PLAYER-ID = %i\n", id);
		//player.ID = id;
		set_nb(Server_socket);
		//message = calloc(1, 50);
	}
	/// <summary>
	/// Send a series of bytes to the IP Server_Socket
	/// </summary>
	/// <param name="data"></param>
	/// <returns></returns>
	int send_to_server(unsigned char* data)
	{
		int sent_bytes = sendto(Server_socket, (char*)data, 50, 0, (struct sockaddr*)&Server_addr, sizeof(Server_addr));
		if (sent_bytes < 0)
		{
			 puts("Send failed");
			return 1;
		}
		return 0;
	
	}
	unsigned long GetIncomingPacketNumber()
	{
		unsigned long msg_length;
		int error = ioctlsocket(Server_socket, FIONREAD, &msg_length);
		
		return msg_length;
	}
	int ReceiveFromServer(unsigned char* buffer,int buffer_length)
	{
		int server_size = sizeof(Server_addr);
		return recvfrom(Server_socket, (char*)buffer, buffer_length, 0, (struct sockaddr*)&(Server_addr), &server_size);
	}
};