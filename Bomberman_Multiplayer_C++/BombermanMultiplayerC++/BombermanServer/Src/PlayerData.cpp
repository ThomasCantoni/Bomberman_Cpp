#include "PlayerData.h"
#include "NETPhysicsMgr.h"
#include "NETColliderFactory.h"
#include "NETCollider.h"
namespace Bomberman
{

	PlayerData::PlayerData(const float x, const float y, const float w, const float h) : ActorData(x, y, w, h)
	{
		
		rigidbody = std::make_shared<NETRigidBody>(this);
		
		 
		rigidbody->Collider = std::reinterpret_pointer_cast<NETCollider>(NETColliderFactory::CreateBoxFor(this));
		rigidbody->AddCollisionType(RigidBodyType::Wall);
		rigidbody->Type = RigidBodyType::Player;
		rigidbody->velocityMultiplier = DEFAULT_PLAYER_SPEED_VEC;
		NETPhysicsMgr::AddItem(rigidbody);
		
	}
}