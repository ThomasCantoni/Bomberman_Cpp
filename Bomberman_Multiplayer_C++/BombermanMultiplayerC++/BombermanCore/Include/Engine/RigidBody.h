#pragma once
#include "Vector2.h"
#include "Actor.h"

#include "Collider.h"
//#include "PhysicsMgr.h"
namespace Bomberman
{
	//class Collider;
	//class Collision;
	class PhysicsMgr;
	enum class RigidBodyType { Wall = 1, Egg = 2, Player = 4 };

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
		void Update() override;
		void AddCollisionType(RigidBodyType type);
		void AddCollisionType(unsigned int value);
		bool CollisionTypeMatches(RigidBodyType type);
		bool IsAwake();

		bool Collides(RigidBody* other, Collision* collisionInfo);
		


		virtual ~RigidBody() override;


	};
	
}
