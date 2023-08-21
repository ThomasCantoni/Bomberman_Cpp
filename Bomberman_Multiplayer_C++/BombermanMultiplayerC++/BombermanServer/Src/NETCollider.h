#pragma once
#include "Vector2.h"
//#include "RigidBody.h"
//#include "BoxCollider.h"
#include "NETCollision.h"
//#include "NETCollisionType.h"
namespace Bomberman
{
	class BoxCollider;
	class NETRigidBody;
	class Actor;


	


	class NETCollider
	{
	public:
		Vector2 offset;
		NETRigidBody* rigidbody;

		NETCollider(NETRigidBody* owner);
		Vector2 GetPosition();

		virtual bool Collides(NETCollider* collider, NETCollision* collisionInfo)=0;
		virtual bool Collides(BoxCollider* collider, NETCollision* collisionInfo)=0;
		//bool Collides(CircleCollider circle, ref Collision collisionInfo);
		//bool Collides(CompoundCollider compound, ref Collision collisionInfo);
		virtual bool Contains(Vector2 point) =0;

	};

}