#include "RigidBody.h"
#include "PhysicsMgr.h"
#include "Collider.h"
namespace Bomberman
{
	RigidBody::RigidBody(Actor* owner)
	{
		Owner = owner;
		PhysicsMgr::AddItem(this);
		velocity = Vector2::Zero();
		velocityMultiplier = Vector2::One();
		friction = Vector2::Zero();
	}
	bool RigidBody::IsActive()
	{
		return Owner->IsActive;
	}
	void RigidBody::SetStatic(bool desiredValue)
	{
		IsStatic = desiredValue;
	}
	Vector2 RigidBody::GetPosition()
	{
		return Owner->transform.GetPosition();
	}
	void RigidBody::Update()
	{
		
		//std::cout << "AAAAAAAAAAAAA" << velocity.x << " " << velocity.y << " " << std::endl;
		if (IsStatic == true)
		{
			velocity = Vector2::Zero();
			return;
		}
		Owner->transform.AddVelocity(velocity * velocityMultiplier );
		velocity.x /= 1 +friction.x * Time::DeltaTime;
		velocity.y /= 1 +friction.y * Time::DeltaTime;
	}
	void RigidBody::AddCollisionType(RigidBodyType type)
	{
		collisionMask |= (unsigned int)type;
	}
	void RigidBody::AddCollisionType(unsigned int type)
	{
		collisionMask |= (unsigned int)type;
	}
	bool RigidBody::CollisionTypeMatches(RigidBodyType type)
	{
		return ((unsigned int)type & collisionMask) != 0;
	}
	bool RigidBody::Collides(RigidBody* other, Collision* collisionInfo)
	{
		return Collider->Collides(other->Collider, collisionInfo);
	}
	RigidBody::~RigidBody()
	{
		PhysicsMgr::RemoveItem(this);
	}
}