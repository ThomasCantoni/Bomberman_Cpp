#pragma once
#include "Vector2.h"
//#include "RigidBody.h"
//#include "BoxCollider.h"
namespace Bomberman
{
	enum CollisionType { None, RectsIntersection, CirclesIntersection, CircleRectIntersection };
	class BoxCollider;
	class RigidBody;
	class Actor;

	struct Collision
	{
	public:
		Actor* Collider;
		Vector2 Delta;
		CollisionType Type;
	};


	class Collider
	{
	public:
		Vector2 offset;
		RigidBody* rigidbody;

		Collider(RigidBody* owner);
		Vector2 GetPosition();

		virtual bool Collides(Collider* collider, Collision* collisionInfo)=0;
		virtual bool Collides(BoxCollider* collider, Collision* collisionInfo)=0;
		//bool Collides(CircleCollider circle, ref Collision collisionInfo);
		//bool Collides(CompoundCollider compound, ref Collision collisionInfo);
		virtual bool Contains(Vector2 point) =0;

	};

}