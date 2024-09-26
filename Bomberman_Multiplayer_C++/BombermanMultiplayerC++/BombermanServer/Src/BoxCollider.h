#pragma once
#include "NETCollider.h"
#include <math.h>
namespace Bomberman
{
	//class Collider* c;
class BoxCollider : public NETCollider
{
protected:

	float halfWidth;
	float halfHeight;

public:
	float GetWidth()
	{
		return halfWidth * 2;
	}
	float GetHeight()
	{
		return halfHeight * 2;
	}

	BoxCollider(std::shared_ptr<NETRigidBody>  owner, float w, float h);
	bool Contains(Vector2 point) override;


	bool Collides(std::shared_ptr<NETCollider> other, NETCollision* collisionInfo) const override;
	bool Collides(std::shared_ptr<BoxCollider> other, NETCollision *collisionInfo) const override;
	bool Collides(const NETCollider& other, NETCollision* collisionInfo) const override;
	bool Collides(const BoxCollider& other, NETCollision* collisionInfo) const override;

	//{
	//	return collider.Collides(this, ref collisionInfo);
	//}

	/*bool Collides(CircleCollider circle, ref Collision collisionInfo)
	{
		float deltaX = circle.Position.X -
			Math.Max(Position.X - halfWidth,
				Math.Min(circle.Position.X, Position.X + halfWidth));

		float deltaY = circle.Position.Y -
			Math.Max(Position.Y - halfHeight,
				Math.Min(circle.Position.Y, Position.Y + halfHeight));

		collisionInfo.Type = CollisionType.CircleRectIntersection;
		collisionInfo.Delta = new Vector2(deltaX, deltaY);
		return (deltaX * deltaX + deltaY * deltaY) < (circle.Radius * circle.Radius);
	}*/



	/*bool Collides(CompoundCollider compound, ref Collision collisionInfo) override;
	{
		return compound.Collides(this, ref collisionInfo);
	}*/
};
}