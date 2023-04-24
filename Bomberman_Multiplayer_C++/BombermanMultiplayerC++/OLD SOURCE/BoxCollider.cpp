#include "BoxCollider.h"
namespace Bomberman
{
	BoxCollider::BoxCollider(RigidBody* owner, float w, float h) : Collider(owner)
	{

		halfWidth = w * 0.5f;
		halfHeight = h * 0.5f;

	}

	bool BoxCollider::Collides(Collider* collider, Collision* collisionInfo)
	{
		return collider->Collides(this, collisionInfo);
	}
	bool BoxCollider::Collides(BoxCollider* other, Collision* collisionInfo)
	{
		Vector2 distance = other->GetPosition() - GetPosition();
		float deltaX = fabs (distance.x) - (other->halfWidth + BoxCollider::halfWidth);

		if (deltaX > 0)
		{
			return false;
		}

		float deltaY = fabs(distance.y) - (other->halfHeight + BoxCollider::halfHeight);

		if (deltaY > 0)
		{
			return false;
		}
		
		collisionInfo->Type = CollisionType::RectsIntersection;
		collisionInfo->Delta = Vector2(-deltaX, -deltaY);//in order to have positive values

		return true;
	}
	bool BoxCollider::Contains(Vector2 point)
	{

		Vector2 Position = GetPosition();
		return
			point.x >= Position.x - halfWidth &&
			point.x <= Position.x + halfWidth &&
			point.y >= Position.y - halfHeight &&
			point.y <= Position.y + halfHeight;

	}
}