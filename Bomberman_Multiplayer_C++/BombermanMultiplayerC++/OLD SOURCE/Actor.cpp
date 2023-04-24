#include "Actor.h"
#include "RigidBody.h"
#include "Collider.h"
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
		rigidbody = new RigidBody(this);
		////SDL_setTex
		transform.pivot.x =  0.5f;
		transform.pivot.y =  0.5f;
		transform.SetDimensions(Vector2(t->w, t->h));
		transform.SetPosition( Vector2(0,0));
		/*SDL_UpdateTexture(texture, NULL, pixels->pixels, pixels->w * 4);
		
		SDL_SetTextureAlphaMod(texture, 255);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_FreeSurface(pixels);*/
		
		//SDL_FreeSurface(pixels->pixels);
		//SDL_free(pixels);
		//delete(pixels);
		//std::unique_ptr<IUpdatable> thisClass = this;
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

		//SDL_rect	=	other.SDL_rect;
		//texture		=	other.texture;
		//pivot	    =	other.pivot;

	}
	void Actor::Update()
	{
		SDL_RenderCopy(SDL_Object::renderer, texture, NULL, &transform.SDL_rect);;
	}
	
	void Actor::OnCollide(Collision& collisionInfo)
	{
		if (rigidbody->IsStatic)
		{
			//if i am static, i do nothing
			return;
		}
		if (collisionInfo.Collider->rigidbody->IsStatic)
		{
			//OnCollideWithDynamic(collisionInfo);

			OnCollideWithStatic(collisionInfo);
		

		}
		else
		{
			OnCollideWithDynamic(collisionInfo);

		}
		
		
	}
	void Actor::OnCollideWithStatic(Collision& collisionInfo)
	{
		
		//if (collisionInfo->Collider->rigidbody->IsStatic == false)
		//	return; // static on static collision, makes no sense to 
		Vector2 current_pos = transform.GetPosition();
		Vector2 other_pos = collisionInfo.Collider->transform.GetPosition();
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
		transform.SetPosition(current_pos);
	}
	void Actor::OnCollideWithDynamic(Collision& collisionInfo)
	{
		std::cout << this << " ####################################### DYNAMIC COLLISION" << std::endl;
		Vector2 current_pos = transform.GetPosition();
		Vector2 other_pos   = collisionInfo.Collider->transform.GetPosition();
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
			rigidbody->velocity.y += my_delta.y *0.33f;

			
		}
		
		transform.SetPosition(current_pos);
		//Vector2 exchanger = collisionInfo->Collider->rigidbody->velocity;
		//rigidbody->velocity += collisionInfo.Collider->rigidbody->velocity * 0.5f;
		//rigidbody->velocity = ;
		//rigidbody->velocity = rigidbody->velocity + exchanger * -1.0f * 0.5f;

	}
	std::shared_ptr<INetObjectInfo> Actor::Serialize() const
	{
		//unsigned char* Network_ID;
		
		unsigned char* buffer_x;
		unsigned char* buffer_y;
		auto data = std::make_shared<INetObjectInfo>();
		data.get()->length = 8;
		data.get()->data = new unsigned char[8];

		Vector2 pos = transform.GetPosition();
		//Network_ID = byteconverter::IntToBytes(id);
		buffer_x = byteconverter::FloatToBytes(pos.x);
		buffer_y = byteconverter::FloatToBytes(pos.y);
		byteconverter::BytesAppend(data.get()->data, 8, 0, buffer_x, sizeof(float));
		byteconverter::BytesAppend(data.get()->data, 8, 4, buffer_y, sizeof(float));
		return data;
	}

}
