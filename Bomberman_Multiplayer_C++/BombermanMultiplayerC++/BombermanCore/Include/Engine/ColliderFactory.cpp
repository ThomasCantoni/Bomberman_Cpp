#include "ColliderFactory.h"
#include "RigidBody.h"
#include "BoxCollider.h"
namespace Bomberman
{

	BoxCollider* ColliderFactory::CreateBoxFor(Actor* owner)
	{
		Vector2 dimensions = owner->transform.GetDimensions();
		return new BoxCollider(owner->rigidbody, dimensions.x, dimensions.y);
	}
	BoxCollider* ColliderFactory::CreateBoxFor(Actor* owner, float halfwidth, float halfheight)
	{

		return new BoxCollider(owner->rigidbody, halfwidth * 2, halfheight * 2);
	}
	
}