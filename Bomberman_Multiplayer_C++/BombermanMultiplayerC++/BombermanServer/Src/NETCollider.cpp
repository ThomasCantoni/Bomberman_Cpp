#include "NETCollider.h"
#include "NETRigidBody.h"

namespace Bomberman
{
	//class RigidBody;
	NETCollider::NETCollider(std::shared_ptr<NETRigidBody>  owner)
	{
		rigidbody = owner;
		offset = Vector2::Zero();
	}
	Vector2 NETCollider::GetPosition() const
	{
		
		
		return rigidbody->Owner->ObjectTransform.GetPosition();
		
	}

}