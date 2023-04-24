#pragma once

#include "Collider.h"
//#include "BoxCollider.h"
namespace Bomberman
{
	class BoxCollider;
	class ColliderFactory
	{
	public:
		static BoxCollider* CreateBoxFor(Actor* owner);

		static BoxCollider* CreateBoxFor(Actor* owner, float widthMultiplier, float heightMultiplier);

	};

}