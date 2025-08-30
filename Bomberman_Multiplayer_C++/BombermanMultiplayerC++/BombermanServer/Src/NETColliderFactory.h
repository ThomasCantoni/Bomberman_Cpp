#pragma once

#include "NETCollider.h"
//#include "BoxCollider.h"
namespace Bomberman
{
	class BoxCollider;
	class NETColliderFactory
	{
	public:
<<<<<<< HEAD
		static std::shared_ptr<BoxCollider> CreateBoxFor(ServerActor* owner) ;

		static  std::shared_ptr<BoxCollider> CreateBoxFor(ServerActor* owner, float widthMultiplier, float heightMultiplier);
=======
		static std::shared_ptr<BoxCollider> CreateBoxFor(ActorData* owner) ;

		static  std::shared_ptr<BoxCollider> CreateBoxFor(ActorData* owner, float widthMultiplier, float heightMultiplier);
>>>>>>> main

	};
}