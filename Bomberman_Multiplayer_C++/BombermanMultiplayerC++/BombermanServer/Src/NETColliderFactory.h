#pragma once

#include "NETCollider.h"
//#include "BoxCollider.h"
namespace Bomberman
{
	class BoxCollider;
	class NETColliderFactory
	{
	public:
		static std::shared_ptr<BoxCollider> CreateBoxFor(ActorData* owner) ;

		static  std::shared_ptr<BoxCollider> CreateBoxFor(ActorData* owner, float widthMultiplier, float heightMultiplier);

	};
}