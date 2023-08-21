#include "PlayerData.h"
#include "NETPhysicsMgr.h"
namespace Bomberman
{
	PlayerData::PlayerData(const float x, const float y, const float w, const float h) : ActorData(x, y, w, h)
	{
		rigidbody = new NETRigidBody(this);
		rigidbody->velocityMultiplier = Vector2(5, 5);
		NETPhysicsMgr::AddItem(rigidbody);
		
	}
}