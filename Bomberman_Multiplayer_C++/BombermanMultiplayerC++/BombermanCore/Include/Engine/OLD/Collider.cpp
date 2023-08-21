#include "Collider.h"
#include "RigidBody.h"
namespace Bomberman
{
	//class RigidBody;
	Collider::Collider(RigidBody* owner)
	{
		rigidbody = owner;
		offset = Vector2::Zero();
	}
	Vector2 Collider::GetPosition()
	{

		return rigidbody->Owner->transform.GetPosition();
	}

}