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


namespace Bomberman
{

	class RigidBody;
	struct Collision;
	struct NetworkPacket;
	class Actor : public IUpdatable
	{

	public:
		Transform transform; // for render purposes, position is mostly decided by the server
		SDL_Texture* texture;
		int ID;

		bool IsActive = true;
		

		Actor();
		virtual ~Actor() override;
		Actor(const Actor& other);
		Actor& operator=(const Actor& other) = default;
		Actor(const char* texture_path);

		virtual std::shared_ptr<NetworkPacket> GetPacketTransform() const;
		void Update() override;
		
	};
}

