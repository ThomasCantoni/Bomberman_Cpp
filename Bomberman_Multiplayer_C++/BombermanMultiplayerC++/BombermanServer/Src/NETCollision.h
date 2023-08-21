#pragma once
#include "ActorData.h"
#include "NETCollisionType.h"
namespace Bomberman
{

	
	struct NETCollision
	{
	public:
		ActorData* Collider;
		Vector2 Delta;
		NETCollisionType Type;
	};
}