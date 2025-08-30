#pragma once
#include "Engine/Vector2.h"
#include "Engine/RigidbodyType.h"
#include <memory>
//#include "Collider.h"

//#include "PhysicsMgr.h"
namespace Bomberman {
	class NETCollider;
	class NETCollision;
	class NETPhysicsMgr;
	class ActorData;

	class NETRigidBody : public std::enable_shared_from_this<NETRigidBody>
	{
	protected:
		unsigned int collisionMask;
		bool isActive;
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
		std::shared_ptr<NETCollider> Collider;

		bool IsActive();
		void SetStatic(bool desiredValue);
		
		Vector2 GetPosition();
		NETRigidBody(ActorData* owner);
		//NETRigidBody();

		void Update();
		void AddCollisionType(RigidBodyType type);
		void AddCollisionType(unsigned int value);
		bool CollisionTypeMatches(RigidBodyType type);
		bool IsAwake();

		bool Collides(std::shared_ptr<NETRigidBody> other, NETCollision* collisionInfo);



		virtual ~NETRigidBody() ;


	};

}
