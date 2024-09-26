#include "BoxCollider.h"
namespace Bomberman
{
	BoxCollider::BoxCollider(std::shared_ptr<NETRigidBody> owner, float w, float h) : NETCollider(owner) 
	{

		halfWidth = w * 0.5f;
		halfHeight = h * 0.5f;

	}
	bool BoxCollider::Collides(const NETCollider& collider, NETCollision* collisionInfo) const
	{
		
		return collider.Collides(*this, collisionInfo);
	}
	bool BoxCollider::Collides(std::shared_ptr<NETCollider> collider, NETCollision* collisionInfo) const
	{
	
		return collider->Collides(*this, collisionInfo);
	}
	bool BoxCollider::Collides(const BoxCollider& other, NETCollision* collisionInfo) const
	{
		Vector2 distance = other.GetPosition() - GetPosition();
		float deltaX = fabs(distance.x) - (other.halfWidth + BoxCollider::halfWidth);

		if (deltaX > 0)
		{
			return false;
		}

		float deltaY = fabs(distance.y) - (other.halfHeight + BoxCollider::halfHeight);

		if (deltaY > 0)
		{
			return false;
		}

		collisionInfo->Type = NETCollisionType::RectsIntersection;
		collisionInfo->Delta = Vector2(-deltaX, -deltaY);//in order to have positive values

		return true;
	}
	bool BoxCollider::Collides(std::shared_ptr<BoxCollider> other, NETCollision* collisionInfo) const
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
		
		collisionInfo->Type = NETCollisionType::RectsIntersection;
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