#pragma once
#include "ActorData.h"
namespace Bomberman
{

<<<<<<< HEAD
	class ServerTile : public ServerActor
=======
	class ServerTile : public ActorData
>>>>>>> main
	{
	private:
		bool isStatic = false;
	public:
		//std::shared_ptr<NETRigidBody> rigidbody;
		ServerTile(const float x, const float y, const float w, const float h, const bool IsStatic = true);
		
		~ServerTile() = default;
		
	};
}

