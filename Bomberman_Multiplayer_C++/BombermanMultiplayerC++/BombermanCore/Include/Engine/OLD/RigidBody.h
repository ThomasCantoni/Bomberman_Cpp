#pragma once
#include "Vector2.h"
#include "Actor.h"
#include "RigidbodyType.h"
#include "Collider.h"
//#include "PhysicsMgr.h"
namespace Bomberman
{
	//class Collider;
	//class Collision;
	class PhysicsMgr;


	class RigidBody : public IUpdatable
	{
	protected:
		unsigned int collisionMask;
	public:
		Vector2 velocity;
		Vector2 velocityMultiplier;
		Vector2 friction;


		Actor* Owner;
		bool IsGravityAffected;
		bool IsStatic = false;
		bool IsCollisionsAffected = true;

		//float Friction;

		RigidBodyType Type;
		Collider* Collider;

		bool IsActive();
		void SetStatic(bool desiredValue);

		Vector2 GetPosition();
		RigidBody(Actor* owner);
		RigidBody();

		void Update() override;
		void AddCollisionType(RigidBodyType type);
		void AddCollisionType(unsigned int value);
		bool CollisionTypeMatches(RigidBodyType type);
		bool IsAwake();

		bool Collides(RigidBody* other, Collision* collisionInfo);
		


		virtual ~RigidBody() override;


	};
	
}
