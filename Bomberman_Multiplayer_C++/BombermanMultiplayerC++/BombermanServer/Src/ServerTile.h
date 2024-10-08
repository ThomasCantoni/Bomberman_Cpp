#pragma once
#include "ActorData.h"
namespace Bomberman
{

	class ServerTile : public ActorData
	{
	private:
		bool isStatic = false;
	public:
		//std::shared_ptr<NETRigidBody> rigidbody;
		ServerTile(const float x, const float y, const float w, const float h, const bool IsStatic = true);
		
		~ServerTile() = default;
		
	};
}

