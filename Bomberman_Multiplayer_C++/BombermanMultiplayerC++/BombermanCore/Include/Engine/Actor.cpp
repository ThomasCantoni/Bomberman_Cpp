#include "Actor.h"
#include "NetworkBase.h"
namespace Bomberman
{
	Actor::Actor()
	{
		IsActive = true;
		transform.pivot.x = 0.5f;
		transform.pivot.y = 0.5f;
	}
	Actor::Actor(const char* textureName)
	{
		IsActive = true;
		TextureStruct* t = TextureFactory::GetTexture(textureName);
		texture = t->texture;

		//TO DO: Rigidbody should be requested from server
		//rigidbody = new RigidBody(this);

		transform.pivot.x =  0.5f;
		transform.pivot.y =  0.5f;
		transform.SetDimensions(Vector2((float)t->w, (float)t->h));
		transform.SetPosition( Vector2(0,0));
		
		UpdateMgr::AddItem(this);
		puts("PLAYER COMPLETED");
	}
	
	Actor::~Actor()
	{
		IsActive = false;
		UpdateMgr::RemoveItem(this);
		
	}
	Actor::Actor(const Actor& other)
	{


	}
	void Actor::Update()
	{
		SDL_RenderCopy(SDL_Object::renderer, texture, NULL, &transform.SDL_rect);;
	}
	
	#pragma region OLD
	//
	//void Actor::OnCollide(Collision& collisionInfo)
		//{
		//	if (rigidbody->IsStatic)
		//	{
		//		//if i am static, i do nothing
		//		return;
		//	}
		//	if (collisionInfo.Collider->rigidbody->IsStatic)
		//	{
		//		//OnCollideWithDynamic(collisionInfo);

		//		OnCollideWithStatic(collisionInfo);
		//	

		//	}
		//	else
		//	{
		//		OnCollideWithDynamic(collisionInfo);

		//	}
		//	
		//	
		//}
		//void Actor::OnCollideWithStatic(Collision& collisionInfo)
		//{
		//	
		//	//if (collisionInfo->Collider->rigidbody->IsStatic == false)
		//	//	return; // static on static collision, makes no sense to 
		//	Vector2 current_pos = transform.GetPosition();
		//	Vector2 other_pos = collisionInfo.Collider->transform.GetPosition();
		//	Vector2 my_delta = collisionInfo.Delta;
		//	
		//	if (collisionInfo.Delta.x < collisionInfo.Delta.y)
		//	{
		//		//horizontal collision
		//		if (current_pos.x < other_pos.x)
		//		{
		//			//collision from right
		//			my_delta.x *= -1.0f;
		//			
		//			std::cout << this << " COLLISION FROM RIGHT" << std::endl;
		//		}
		//		else
		//		{
		//			//collision from left
		//			std::cout << this << " COLLISION FROM LEFT" << std::endl;
		//		
		//		}
		//		current_pos.x += my_delta.x;
		//		
		//		//rigidbody->velocity.x += collisionInfo.Delta.x * 0.8f;
		//		//rigidbody->velocity.x += collisionInfo.Collider->rigidbody->velocity.x* 0.6f;
		//		//transform.SetPosition(current_pos);
		//		//rigidbody->velocityMultiplier.x = 0;


		//	}
		//	else
		//	{
		//		//vertical collision
		//		if (current_pos.y < other_pos.y)
		//		{
		//			//collision from top
		//			my_delta.y *= -1.0f;
		//			std::cout << this << " COLLISION FROM ABOVE" << std::endl;

		//		}
		//		else
		//		{
		//			//collision from bottom
		//			std::cout << this << " COLLISION FROM BOTTOM" << std::endl;
		//		}
		//		current_pos.y += my_delta.y;
		//		//rigidbody->velocity.y = collisionInfo->Delta.y * 0.8f;
		//		//rigidbody->velocity.y += collisionInfo.Collider->rigidbody->velocity.y * 0.6f;

		//		//current_pos.y += collisionInfo->Delta.y;
		//		//std::cout << "YYYYYYYYYYYYYYYYYYYYYYYYYYYYY" << std::endl;
		//	}
		//	transform.SetPosition(current_pos);
		//}
		//void Actor::OnCollideWithDynamic(Collision& collisionInfo)
		//{
		//	std::cout << this << " ####################################### DYNAMIC COLLISION" << std::endl;
		//	Vector2 current_pos = transform.GetPosition();
		//	Vector2 other_pos   = collisionInfo.Collider->transform.GetPosition();
		//	Vector2 my_delta = collisionInfo.Delta;
		//	if (collisionInfo.Delta.x < collisionInfo.Delta.y)
		//	{
		//		//horizontal collision
		//		if (current_pos.x < other_pos.x)
		//		{//collision from right			
		//			my_delta.x *= -1.0f;
		//			std::cout << this << " COLLISION FROM RIGHT" << std::endl;
		//		}
		//		else
		//		{//collision from left
		//			std::cout << this << " COLLISION FROM LEFT" << std::endl;
		//			//collisionInfo->Delta.x = collisionInfo->Delta.x;
		//		}

		//		current_pos.x += my_delta.x;
		//		rigidbody->velocity.x += my_delta.x * 0.33f;
		//	}
		//	else
		//	{
		//		//vertical collision
		//		if (current_pos.y < other_pos.y)
		//		{//collision from top
		//			
		//			my_delta.y *= -1.0f;
		//			std::cout << this << " COLLISION FROM ABOVE" << std::endl;
		//		}
		//		else
		//		{//collision from bottom
		//			
		//			//collisionInfo->Delta.y = collisionInfo->Delta.y;
		//			std::cout << this << " COLLISION FROM BOTTOM" << std::endl;
		//		}
		//		
		//		current_pos.y += my_delta.y;
		//		rigidbody->velocity.y += my_delta.y *0.33f;

		//		
		//	}
		//	
		//	transform.SetPosition(current_pos);
		//	//Vector2 exchanger = collisionInfo->Collider->rigidbody->velocity;
		//	//rigidbody->velocity += collisionInfo.Collider->rigidbody->velocity * 0.5f;
		//	//rigidbody->velocity = ;
		//	//rigidbody->velocity = rigidbody->velocity + exchanger * -1.0f * 0.5f;

		//}  
#pragma endregion

	std::shared_ptr<SerialData> Actor::GetPacketTransform() const
	{
		auto serialTr = transform.Serialize();

		auto  d = std::make_shared<SerialData>(sizeof(int) * 2);
		byteconverter::BytesAppend(d->data, d->length, 0, ID);
		byteconverter::BytesAppend(d->data, d->length, 4, (int)NETCOMMANDType::Update);

		d->Append(*serialTr.get());
		d->Print();

		return d;
		
		
		
	}

}
