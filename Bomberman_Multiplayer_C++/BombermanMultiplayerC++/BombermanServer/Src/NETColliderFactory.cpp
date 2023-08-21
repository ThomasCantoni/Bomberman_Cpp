#include "NETColliderFactory.h"
#include "NETRigidBody.h"
#include "BoxCollider.h"
namespace Bomberman
{

	BoxCollider* ColliderFactory::CreateBoxFor(ActorData* owner)
	{
		Vector2 dimensions = owner->ObjectTransform.GetDimensions();
		return new BoxCollider(owner->rigidbody, dimensions.x, dimensions.y);
	}
	BoxCollider* ColliderFactory::CreateBoxFor(ActorData* owner, float halfwidth, float halfheight)
	{

		return new BoxCollider(owner->rigidbody, halfwidth * 2, halfheight * 2);
	}
	
}