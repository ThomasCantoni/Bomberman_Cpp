#include "ServerTile.h"
//#include "RigidbodyType.h"
#include "NETRigidBody.h"
#include "NETColliderFactory.h"
namespace Bomberman
{
	ServerTile::ServerTile(const float x, const float y, const float w, const float h, const bool isStatic) : ServerActor(x,y,w,h)
	{

		//ObjectTransform.SetDimensions(Vector2(w, h));
		//ObjectTransform.SetPosition(Vector2(x, y));

		this->isStatic = isStatic;
		rigidbody = std::make_shared<NETRigidBody>(this);
		//rigidbody->SetStatic(isStatic);
		//rigidbody->friction = Vector2::One() * 2.f;
		auto bruh = std::reinterpret_pointer_cast<NETCollider>(NETColliderFactory::CreateBoxFor(this));
		rigidbody->Collider = bruh;
		rigidbody->AddCollisionType(RigidBodyType::Player);
		rigidbody->AddCollisionType(RigidBodyType::Wall);

		rigidbody->Type = RigidBodyType::Wall;
	}


}