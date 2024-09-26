#include "NETColliderFactory.h"
#include "NETRigidBody.h"
#include "BoxCollider.h"
 
namespace Bomberman
{

	std::shared_ptr<BoxCollider> NETColliderFactory::CreateBoxFor(ActorData* owner)
	{
		Vector2 dimensions = owner->ObjectTransform.GetDimensions();
		return std::make_shared< BoxCollider>(owner->rigidbody, dimensions.x, dimensions.y);
	}
	std::shared_ptr<BoxCollider>NETColliderFactory::CreateBoxFor(ActorData* owner, float halfwidth, float halfheight)
	{

		return std::make_shared< BoxCollider>(owner->rigidbody, halfwidth * 2, halfheight * 2);
	}
	
}