#pragma once
#include "ActorData.h"
#include "NETCollisionType.h"
namespace Bomberman
{

	
	struct NETCollision
	{
	public:
		ServerActor* Collider;
		Vector2 Delta;
		NETCollisionType Type;
	};
}