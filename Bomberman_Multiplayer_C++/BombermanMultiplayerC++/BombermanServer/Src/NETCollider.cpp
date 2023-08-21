#include "NETCollider.h"
#include "NETRigidBody.h"
namespace Bomberman
{
	//class RigidBody;
	NETCollider::NETCollider(NETRigidBody* owner)
	{
		rigidbody = owner;
		offset = Vector2::Zero();
	}
	Vector2 NETCollider::GetPosition()
	{
		return rigidbody->Owner->ObjectTransform.GetPosition();
		
	}

}