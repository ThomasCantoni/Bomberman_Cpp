#include "Actor.h"
#include "NetworkBase.h"
#include "NetworkPacket.h"

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


		transform.pivot.x =  0.5f;
		transform.pivot.y =  0.5f;
		transform.SetDimensions(Vector2((float)t->w, (float)t->h));
		transform.SetPosition( Vector2(0,0));
		
		UpdateMgr::AddItem(this);
		
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
		SDL_RenderCopy(SDL_Object::renderer, texture, NULL, &transform.screenTransform);;
	}
	

	std::shared_ptr<NetworkPacket> Actor::GetPacketTransform() const
	{
		auto net = std::make_shared<NetworkPacket>(NETCOMMANDType::Update,ID, transform.Serialize());
		return net;
		
		
		
	}

}
