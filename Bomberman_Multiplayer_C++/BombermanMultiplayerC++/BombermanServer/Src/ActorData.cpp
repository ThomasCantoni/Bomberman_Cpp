#include "ActorData.h"
#include "NetworkBase.h"
#include "LocalMap.h"
#include "NETCollision.h"
#include "NETRigidBody.h"
namespace Bomberman
{



ActorData::ActorData(float x, float y, float w, float h)
{
	
	ObjectTransform.SetPosition(x, y);
	ObjectTransform.SetDimensions(w, h);

}
ActorData::ActorData(Transform t)
{
	ObjectTransform = t;


}
std::shared_ptr<SerialData> ActorData::GetPacketAnnounce()
{
	return NULL;
}
std::shared_ptr<SerialData> ActorData::GetPacketDeath()
{
	return NULL;
}
std::shared_ptr<SerialData> ActorData::GetPacketTransform()
{
	return ObjectTransform.Serialize();
}


void ActorData::OnCollide(NETCollision& collisionInfo)
{
	if (rigidbody->IsStatic)
	{
		//if i am static, i do nothing
		return;
	}
	if (collisionInfo.Collider->rigidbody)
	{
		//OnCollideWithDynamic(collisionInfo);

		OnCollideWithStatic(collisionInfo);


	}
	else
	{
		OnCollideWithDynamic(collisionInfo);

	}


}
void ActorData::OnCollideWithStatic(NETCollision& collisionInfo)
{

	//if (collisionInfo->Collider->rigidbody->IsStatic == false)
	//	return; // static on static collision, makes no sense to 
	Vector2 current_pos = ObjectTransform.GetPosition();
	Vector2 other_pos = collisionInfo.Collider->ObjectTransform.GetPosition();
	Vector2 my_delta = collisionInfo.Delta;

	if (collisionInfo.Delta.x < collisionInfo.Delta.y)
	{
		//horizontal collision
		if (current_pos.x < other_pos.x)
		{
			//collision from right
			my_delta.x *= -1.0f;

			std::cout << this << " COLLISION FROM RIGHT" << std::endl;
		}
		else
		{
			//collision from left
			std::cout << this << " COLLISION FROM LEFT" << std::endl;

		}
		current_pos.x += my_delta.x;

		//rigidbody->velocity.x += collisionInfo.Delta.x * 0.8f;
		//rigidbody->velocity.x += collisionInfo.Collider->rigidbody->velocity.x* 0.6f;
		//transform.SetPosition(current_pos);
		//rigidbody->velocityMultiplier.x = 0;


	}
	else
	{
		//vertical collision
		if (current_pos.y < other_pos.y)
		{
			//collision from top
			my_delta.y *= -1.0f;
			std::cout << this << " COLLISION FROM ABOVE" << std::endl;

		}
		else
		{
			//collision from bottom
			std::cout << this << " COLLISION FROM BOTTOM" << std::endl;
		}
		current_pos.y += my_delta.y;
		//rigidbody->velocity.y = collisionInfo->Delta.y * 0.8f;
		//rigidbody->velocity.y += collisionInfo.Collider->rigidbody->velocity.y * 0.6f;

		//current_pos.y += collisionInfo->Delta.y;
		//std::cout << "YYYYYYYYYYYYYYYYYYYYYYYYYYYYY" << std::endl;
	}
	ObjectTransform.SetPosition(current_pos);
}
void ActorData::OnCollideWithDynamic(NETCollision& collisionInfo)
{
	std::cout << this << " ####################################### DYNAMIC COLLISION" << std::endl;
	Vector2 current_pos = ObjectTransform.GetPosition();
	Vector2 other_pos = collisionInfo.Collider->ObjectTransform.GetPosition();
	Vector2 my_delta = collisionInfo.Delta;
	if (collisionInfo.Delta.x < collisionInfo.Delta.y)
	{
		//horizontal collision
		if (current_pos.x < other_pos.x)
		{//collision from right			
			my_delta.x *= -1.0f;
			std::cout << this << " COLLISION FROM RIGHT" << std::endl;
		}
		else
		{//collision from left
			std::cout << this << " COLLISION FROM LEFT" << std::endl;
			//collisionInfo->Delta.x = collisionInfo->Delta.x;
		}

		current_pos.x += my_delta.x;
		rigidbody->velocity.x += my_delta.x * 0.33f;
	}
	else
	{
		//vertical collision
		if (current_pos.y < other_pos.y)
		{//collision from top

			my_delta.y *= -1.0f;
			std::cout << this << " COLLISION FROM ABOVE" << std::endl;
		}
		else
		{//collision from bottom

			//collisionInfo->Delta.y = collisionInfo->Delta.y;
			std::cout << this << " COLLISION FROM BOTTOM" << std::endl;
		}

		current_pos.y += my_delta.y;
		rigidbody->velocity.y += my_delta.y * 0.33f;


	}

	ObjectTransform.SetPosition(current_pos);
	//Vector2 exchanger = collisionInfo->Collider->rigidbody->velocity;
	//rigidbody->velocity += collisionInfo.Collider->rigidbody->velocity * 0.5f;
	//rigidbody->velocity = ;
	//rigidbody->velocity = rigidbody->velocity + exchanger * -1.0f * 0.5f;

}









}