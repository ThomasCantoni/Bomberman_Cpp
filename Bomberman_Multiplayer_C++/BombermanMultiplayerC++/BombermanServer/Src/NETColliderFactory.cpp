#include "NETColliderFactory.h"
#include "NETRigidBody.h"
#include "BoxCollider.h"
 
namespace Bomberman
{

<<<<<<< HEAD
	std::shared_ptr<BoxCollider> NETColliderFactory::CreateBoxFor(ServerActor* owner)
=======
	std::shared_ptr<BoxCollider> NETColliderFactory::CreateBoxFor(ActorData* owner)
>>>>>>> main
	{
		Vector2 dimensions = owner->ObjectTransform.GetDimensions();
		return std::make_shared< BoxCollider>(owner->rigidbody, dimensions.x, dimensions.y);
	}
<<<<<<< HEAD
	std::shared_ptr<BoxCollider>NETColliderFactory::CreateBoxFor(ServerActor* owner, float halfwidth, float halfheight)
=======
	std::shared_ptr<BoxCollider>NETColliderFactory::CreateBoxFor(ActorData* owner, float halfwidth, float halfheight)
>>>>>>> main
	{

		return std::make_shared< BoxCollider>(owner->rigidbody, halfwidth * 2, halfheight * 2);
	}
	
}