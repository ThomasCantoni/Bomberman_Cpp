#pragma once
#include "Vector2.h"
#include <memory>
//#include "RigidBody.h"
//#include "BoxCollider.h"
#include "NETCollision.h"
//#include "NETCollisionType.h"
namespace Bomberman
{
	class BoxCollider;
	class NETRigidBody;
	class ActorData;


	


	class NETCollider : public std::enable_shared_from_this<NETCollider>
	{
	public:
		Vector2 offset;
		std::shared_ptr<NETRigidBody> rigidbody;

		NETCollider(std::shared_ptr<NETRigidBody> owner);
		Vector2 GetPosition() const;

		virtual bool Collides(std::shared_ptr<NETCollider> collider, NETCollision* collisionInfo)const =0;
		virtual bool Collides(std::shared_ptr<BoxCollider> collider, NETCollision* collisionInfo) const =0;
		virtual bool Collides(const NETCollider& collider, NETCollision* collisionInfo) const = 0;
		virtual bool Collides(const BoxCollider& collider, NETCollision* collisionInfo) const = 0;
		//bool Collides(CircleCollider circle, ref Collision collisionInfo);
		//bool Collides(CompoundCollider compound, ref Collision collisionInfo);
		virtual bool Contains(Vector2 point) =0;

	};

}