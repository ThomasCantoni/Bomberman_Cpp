#pragma once

#include "Player.h"
#include "ColliderFactory.h"
#include <memory>
#define TIMER_DROP_EGGBOMB  6.0f
namespace Bomberman
{
	
	Player::Player(const SDL_Object* SDL_O) : Actor("paperella.png")
	{
		//NM = new NetworkManager("151.70.135.61", 8888);
		
		NetworkManager::Initialize("127.0.0.1", 9999,this);
		ID = NetworkManager::id;
		//position.x = 0;
		//position.y = 0;
		numberOfLives = 1;
		
		score = 0;
		speed = 200;
		
		transform.SetDimensions(64,64 );
		transform.SetPosition(64,64);
		

		rigidbody->Collider =reinterpret_cast<Collider*>( ColliderFactory::CreateBoxFor(this));
		rigidbody->AddCollisionType(RigidBodyType::Wall);
		rigidbody->Type = RigidBodyType::Player;
		
		

		
	}

	Player::~Player()
	{
		
	}
	void Player::Manage_Input()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// puts("PUMPING EVENTS");
			switch (event.type)
			{

			case SDL_QUIT:
				exit(0);

				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_SPACE )
				{
					//Vector2 pos = tGetPosition();
					InstantiateEgg(transform.GetPosition());
				}
				break;
			}
		}
		SDL_PumpEvents();
		keys = SDL_GetKeyboardState(NULL);
		
	}
	void Player::Update() 
	{
		Actor::Update();
		Manage_Input();
		TimerDropEggbomb -= Time::DeltaTime;
		Vector2 velocity;
		//float testX = (keys[SDL_SCANCODE_RIGHT] * speedX	- keys[SDL_SCANCODE_LEFT] * speedXnegative	)	* Time::DeltaTime * speed;
		//float testY = (keys[SDL_SCANCODE_DOWN]  *  speedY	- keys[SDL_SCANCODE_UP]  * speedYnegative	)	* Time::DeltaTime * speed;
		
		velocity.x = (keys[SDL_SCANCODE_RIGHT]  - keys[SDL_SCANCODE_LEFT] );
		velocity.y = (keys[SDL_SCANCODE_DOWN]   - keys[SDL_SCANCODE_UP] );
		velocity = velocity.Normalize() * Time::DeltaTime * speed;
		//testX = testX * (*Time::DeltaTime) * speed;
		//testY = testY * (*Time::DeltaTime) * speed;

		float test = velocity.Magnitude();
		
		rigidbody->velocity = velocity;

		NetworkManager::ManageNetworkOperations();
		

	}
	
	void Player::InstantiateEgg(const Vector2 pos)
	{

		if (TimerDropEggbomb > 0)
		{
			//return;

		}
		TimerDropEggbomb = TIMER_DROP_EGGBOMB;
		NetworkManager::SendEggRequest(pos);
		//egg->SDL_rect.x = x;
		//egg->SDL_rect.y = y;
		//egg->SetCenter();
		//return egg;
	}

    #pragma region OLD
	/*
	* void Player::ManageNetworkOperations()
	{
		unsigned char Network_ID[sizeof(float)];
		unsigned char command[sizeof(int)];

		unsigned char buffer_x[sizeof(float)];
		unsigned char buffer_y[sizeof(float)];

		secondAccumulator += Time::DeltaTime;
		if (secondAccumulator > NETWORK_PERIOD)
		{
			secondAccumulator = 0;
			byteconverter::IntToBytes(ID, Network_ID);
			Vector2 pos = transform.GetPosition();
			byteconverter::FloatToBytes(buffer_x, pos.x);
			byteconverter::FloatToBytes(buffer_y, pos.y);
			byteconverter::IntToBytes(0, command);


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
			NM->send_to_server(message);
		}
		// get info from server
		for (int i = 0; i < 500; ++i)
		{


			unsigned long msg_length = NM->GetIncomingPacketNumber();
			if (msg_length == 0)
				return;


			int n = NM->ReceiveFromServer(message, MSG_SIZE);
			if (n == 0)
				return;
			//printf("Received %d bytesfrom %s : %d : %.*s \n", n, inet_ntop(NM->Server_addr.sin_addr), ntohs(NM->Server_addr.sin_port), n, message);
			NetworkManager::ProcessMessage(message, n);
		}
	}
	void Player::InstantiateEgg    (const unsigned char* message, int playerID) 
	{															
		float X, Y;
		X = byteconverter::BytesToFloat(message, 8, true);
		Y = byteconverter::BytesToFloat(message, 12, true);
		auto new_egg = std::make_unique<Eggbomb*>(new Eggbomb(X, Y));
	}															
	void Player::InstantiatePlayer (const unsigned char* message, int playerID) 
	{															
		OnlinePlayer* newPlayer = new OnlinePlayer(playerID);

		OnlinePlayers[newPlayer->ID - 1] = newPlayer;
	}															
	void Player::UpdateOnlinePlayer(const unsigned char* message, int playerID) 
	{
		if (playerID == ID)
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
	void Player::KillOnlinePlayer  (const unsigned char* message, int playerID) 
	{
		OnlinePlayer* playerSelected = OnlinePlayers[playerID - 1];
		OnlinePlayers[playerID - 1] = NULL;
		UpdateMgr::RemoveItem(playerSelected);
	}
	void Player::ProcessMessage(const unsigned char* message, const int msg_length)
	
	for (int i = 0; i < msg_length; ++i)
	{
		printf("%x", message[i]);
	}
	
	int player_id = byteconverter::BytesToInt_V2(message, 0);
	
	
	printf("\n RECEIVED PLAYERID %i \n", player_id);
	
	int commandCode = byteconverter::BytesToInt_V2(message, 4);
	printf("\n RECEIVED COMMAND %i \n", commandCode);
	NetworkOp methodToCall = NetworkOps[commandCode];
	(this->*methodToCall)(message,player_id);
	
	
	return;
		
		if (commandCode == 0)
		{ // command 0 updates player
			OnlinePlayer* player_selected = OnlinePlayers[player_id - 1];
			float printX, printY;
			printX = byteconverter::BytesToFloat(message, 8, true);
			printY = byteconverter::BytesToFloat(message, 12, true);

			//player_to_update->Update();
			player_selected->old_position.x = player_selected->latest_position.x;
			player_selected->old_position.y = player_selected->latest_position.y;
			player_selected->latest_position.x = printX;
			player_selected->latest_position.y = printY;
			player_selected->lerp_accumulator = 0;
			//std::cout << "#################################################" << std::endl;
			//std::cout << "UPDATE PLAYER" << std::endl;
			//std::cout << "Player ID = " << player_id << std::endl;
			//std::cout << "POSITIONS : " << printX << " " << printY << std::endl;
			//std::cout << "#################################################" << std::endl;

		}
		if (commandCode == 1)
		{ // command 1 is new player
			//std::cout << "#################################################" << std::endl;
			//std::cout << "NEW PLAYER" << std::endl;
			//std::cout << "New Player ID = " << player_id << std::endl;
			//std::cout << "#################################################" << std::endl;

			OnlinePlayer* newPlayer = new OnlinePlayer(player_id);

			OnlinePlayers[newPlayer->ID - 1] = newPlayer;
		}
		if (commandCode == 2)
		{
			//puts("#################################################");
			//puts("PLAYER DIED");
			//puts("#################################################");
			//OnlinePlayer* player_to_delete = OnlinePlayers[player_id - 1];
			OnlinePlayer* player_selected = OnlinePlayers[player_id - 1];
			OnlinePlayers[player_id - 1] = NULL;
			UpdateMgr::RemoveItem(player_selected);
			//playerSelected->~OnlinePlayer();
			//delete(playerSelected);
		}
		if (commandCode == 3)
		{
			//puts("#################################################");
			//puts("PLAYER DROPPEG EGG");
			//puts("#################################################");
			float X, Y;
			X = byteconverter::BytesToFloat(message, 8, true);
			Y = byteconverter::BytesToFloat(message, 12, true);
		
			auto new_egg = std::make_unique<Eggbomb*>(new Eggbomb(X, Y));
			//delete(new_egg);
			//std::cout << new_egg.get()->c_str() << std::endl;
			//Eggbomb* egg = new Eggbomb(X, Y);

		}

		
		
	
	}
	void Player::OnCollide(Collision* collisionInfo)
	{
		if (collisionInfo->Collider->rigidbody->IsStatic == false)
			return;
		Vector2 current_pos = transform.GetPosition();
		if (collisionInfo->Delta.x < collisionInfo->Delta.y)
		{
			//horizontal collision
			if (current_pos.x < collisionInfo->Collider->transform.GetPosition().x)
			{
				//collision from right
				collisionInfo->Delta.x = -collisionInfo->Delta.x;
				std::cout << this << " COLLISION FROM RIGHT" << std::endl;
			}
			else
			{
				//collision from left
				std::cout << this << " COLLISION FROM LEFT" << std::endl;
				collisionInfo->Delta.x = collisionInfo->Delta.x;
			}
			current_pos.x += collisionInfo->Delta.x;
			rigidbody->velocity.x = collisionInfo->Delta.x * 0.8f;
			//transform.SetPosition(current_pos);
			//rigidbody->velocityMultiplier.x = 0;


		}
		else
		{
			//vertical collision
			if (current_pos.y < collisionInfo->Collider->transform.GetPosition().y)
			{
				//collision from top
				collisionInfo->Delta.y = -collisionInfo->Delta.y;
				std::cout << this << " COLLISION FROM ABOVE" << std::endl;
			}
			else
			{
				//collision from bottom
				collisionInfo->Delta.y = collisionInfo->Delta.y;
				std::cout << this << " COLLISION FROM BOTTOM" << std::endl;
			}
			rigidbody->velocity.y = collisionInfo->Delta.y * 0.8f;
			current_pos.y += collisionInfo->Delta.y;
			//std::cout << "YYYYYYYYYYYYYYYYYYYYYYYYYYYYY" << std::endl;
		}
		transform.SetPosition(current_pos);
	}
	*/
#pragma endregion
	
	

	
}

