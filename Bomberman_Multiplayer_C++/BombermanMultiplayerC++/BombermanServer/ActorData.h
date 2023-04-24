#pragma once
#include "Engine/Vector2.h"
#include "Engine/INetObject.h"
#include "Transform.h"

//#include "NetworkBase.h"
namespace Bomberman
{
	class Tile;

class ActorData
{
public:
	Transform ObjectTransform;
	
	ActorData() = default;

	ActorData(float x,float y,float w,float h);
	ActorData(Transform t);

	std::shared_ptr<SerialData> GetPacketTransform();
	std::shared_ptr<SerialData> GetPacketAnnounce();
	std::shared_ptr<SerialData> GetPacketDeath();


		
		

		
};
}

