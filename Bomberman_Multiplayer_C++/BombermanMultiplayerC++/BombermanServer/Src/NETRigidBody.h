#pragma once
#include "Vector2.h"
#include "RigidbodyType.h"
//#include "Collider.h"

//#include "PhysicsMgr.h"
namespace Bomberman {
	class NETCollider;
	class NETCollision;
	class NETPhysicsMgr;
	class ActorData;

	class NETRigidBody
	{
	protected:
		unsigned int collisionMask;
	public:
		Vector2 velocity;
		Vector2 velocityMultiplier;
		Vector2 friction;
		ActorData* Owner;
		bool IsGravityAffected;
		bool IsStatic = false;
		bool IsCollisionsAffected = true;

		//float Friction;

		RigidBodyType Type;
		NETCollider* Collider;

		bool IsActive();
		void SetStatic(bool desiredValue);
		
		Vector2 GetPosition();
		NETRigidBody(ActorData* owner);
		NETRigidBody();

		void Update();
		void AddCollisionType(RigidBodyType type);
		void AddCollisionType(unsigned int value);
		bool CollisionTypeMatches(RigidBodyType type);
		bool IsAwake();

		bool Collides(NETRigidBody* other, NETCollision* collisionInfo);



		virtual ~NETRigidBody() ;


	};

}
