#pragma once

#include "NETCollider.h"
//#include "BoxCollider.h"
namespace Bomberman
{
	class BoxCollider;
	class ColliderFactory
	{
	public:
		static BoxCollider* CreateBoxFor(ActorData* owner);

		static BoxCollider* CreateBoxFor(ActorData* owner, float widthMultiplier, float heightMultiplier);

	};
}