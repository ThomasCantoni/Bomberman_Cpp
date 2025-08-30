#pragma once
#include "ActorData.h"
#include "NETRigidBody.h"
#include <time.h>
namespace Bomberman
{
#define DEFAULT_PLAYER_SPEED 100
#define DEFAULT_PLAYER_SPEED_VEC {100,100}


	class PlayerData : public ServerActor
	{
	public :
		time_t LastPacketDate;

		//NETRigidBody* rigidBody;
		PlayerData();
		PlayerData(const float x, const float y, const float w, const float h);


	};

}
