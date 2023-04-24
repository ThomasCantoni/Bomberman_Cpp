#pragma once
#include "IUpdatable.h"
#include "UpdateMgr.h"
#include <memory>
#include "SDL_image.h"
#include "SDL_Object.h"
#include <iostream>
#include "TextureFactory.h"
#include "INetObject.h"
//#include "RigidBody.h"

//#include "IGraphicObject.h"
#include "Transform.h"

#define NETWORK_PERIOD 0.2f
#define MSG_SIZE 50
namespace Bomberman
{

	class RigidBody;
	struct Collision;
	class Actor : public IUpdatable
	{

	public:
		Transform transform;
		SDL_Texture* texture;
		RigidBody* rigidbody;
		
		//SDL_Rect SDL_rect;
		//Vector2 position;
		bool IsActive = true;
		

		Actor();
		virtual ~Actor() override;
		Actor(const Actor& other);
		Actor& operator=(const Actor& other) = default;
		Actor(const char* texture_path);
		//virtual INetObjectInfo Serialize() const override;
	   
		virtual void OnCollide			  (Collision& collisionInfo);
		virtual void OnCollideWithStatic  (Collision& collisionInfo);
		virtual void OnCollideWithDynamic (Collision& collisionInfo);
		
		void Update() override;
		
	};
}

