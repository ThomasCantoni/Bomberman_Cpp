#pragma once
#include "ActorData.h"
#include <time.h>
namespace Bomberman
{

	class PlayerData : public ActorData
	{
	public :
		time_t LastPacketDate;

		PlayerData();
		PlayerData(const float x, const float y, const float w, const float h);


	};

}
