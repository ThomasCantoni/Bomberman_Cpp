#include "NETRigidBody.h"
#include "NETPhysicsMgr.h"
#include "NETCollider.h"
#include "Engine/BombermanTime.h"


namespace Bomberman {
	/*NETRigidBody::NETRigidBody()
	{
		velocity = Vector2::Zero();
		velocityMultiplier = Vector2::One();
		friction = Vector2::Zero();
	}*/
	NETRigidBody::NETRigidBody(ActorData* owner) : Owner(owner)
	{
		
		NETPhysicsMgr::AddItem(this);
		velocity = Vector2::Zero();
		velocityMultiplier = Vector2::One();
		friction = Vector2::Zero();
		isActive = true;
	}
	bool NETRigidBody::IsActive()
	{
		return isActive;
	}
	bool NETRigidBody::IsAwake()
	{
		return velocity > Vector2::Zero();
	}
	void NETRigidBody::SetStatic(bool desiredValue)
	{
		IsStatic = desiredValue;
		if (IsStatic)
		{
			//BombermanClientMgr::ObjectsToSync.push_back(&Owner->transform);
		}
		else
		{
			//NetworkManager::ObjectsToSync.
		}
	}
	Vector2 NETRigidBody::GetPosition()
	{
		return Owner->ObjectTransform.GetPosition();
	}
	void NETRigidBody::Update()
	{

		//std::cout << "AAAAAAAAAAAAA" << velocity.x << " " << velocity.y << " " << std::endl;
		if (IsStatic == true)
		{
			velocity = Vector2::Zero();
			return;
		}
		
		Owner->ObjectTransform.AddVelocity(velocity.Normalize() * velocityMultiplier * BombermanTime::DeltaTime);
		if (Owner->GetID() == 0x1c && velocity.Magnitude() > 0)
		{
			/*system("cls");
			std::cout << "pos.x :" << GetPosition().x << "\n";
			std::cout << "pos.y :" << GetPosition().y << "\n";
			std::cout << "vel :" << velocity.Magnitude() << "\n";
			if (velocity.Magnitude() > 1 || velocity.Magnitude() == 1)
			{
			std::cout << "";

			}
			*/
		}


		//velocity.x /= 1 + friction.x * BombermanTime::DeltaTime;
		//velocity.y /= 1 + friction.y * BombermanTime::DeltaTime;
	}
	void NETRigidBody::AddCollisionType(RigidBodyType type)
	{
		collisionMask |= (unsigned int)type;
	}
	void NETRigidBody::AddCollisionType(unsigned int type)
	{
		collisionMask |= (unsigned int)type;
	}
	bool NETRigidBody::CollisionTypeMatches(RigidBodyType type)
	{
		return ((unsigned int)type & collisionMask) != 0;
	}
	bool NETRigidBody::Collides(std::shared_ptr<NETRigidBody> other, NETCollision* collisionInfo)
	{

		return Collider->Collides(other->Collider, collisionInfo);
	}
	NETRigidBody::~NETRigidBody()
	{
		NETPhysicsMgr::RemoveItem(shared_from_this());
	}
}