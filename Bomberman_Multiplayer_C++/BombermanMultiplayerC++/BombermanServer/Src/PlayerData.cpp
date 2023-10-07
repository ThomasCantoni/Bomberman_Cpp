#include "PlayerData.h"
#include "NETPhysicsMgr.h"
namespace Bomberman
{
	PlayerData::PlayerData(const float x, const float y, const float w, const float h) : ActorData(x, y, w, h)
	{
		rigidbody = new NETRigidBody(this);
		rigidbody->velocityMultiplier = DEFAULT_PLAYER_SPEED_VEC;
		NETPhysicsMgr::AddItem(rigidbody);
		
	}
}