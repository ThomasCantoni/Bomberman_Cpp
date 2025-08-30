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
	class ClientActor : public IUpdatable
	{

	public:
		Transform transform; // for render purposes, position is mostly decided by the server
		SDL_Texture* texture;
		int ID;

		bool IsActive = true;
		

		ClientActor();
		virtual ~ClientActor() override;
		ClientActor(const ClientActor& other);
		ClientActor& operator=(const ClientActor& other) = default;
		ClientActor(const char* texture_path);

		virtual std::shared_ptr<NetworkPacket> GetPacketTransform() const;
		void Update() override;
		
	};
}

