#pragma once

#include "NETCollider.h"
//#include "BoxCollider.h"
namespace Bomberman
{
	class BoxCollider;
	class NETColliderFactory
	{
	public:
		static std::shared_ptr<BoxCollider> CreateBoxFor(ServerActor* owner) ;

		static  std::shared_ptr<BoxCollider> CreateBoxFor(ServerActor* owner, float widthMultiplier, float heightMultiplier);

	};
}