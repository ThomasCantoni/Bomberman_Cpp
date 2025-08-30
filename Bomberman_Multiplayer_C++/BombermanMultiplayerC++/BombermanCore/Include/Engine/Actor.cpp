#include "Actor.h"
#include "NetworkBase.h"
#include "NetworkPacket.h"

namespace Bomberman
{
	ClientActor::ClientActor()
	{
		IsActive = true;
		transform.pivot.x = 0.5f;
		transform.pivot.y = 0.5f;
	}
	ClientActor::ClientActor(const char* textureName)
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
	
	ClientActor::~ClientActor()
	{
		IsActive = false;
		UpdateMgr::RemoveItem(this);
		
	}
	ClientActor::ClientActor(const ClientActor& other)
	{


	}
	void ClientActor::Update()
	{
		SDL_RenderCopy(SDL_Object::renderer, texture, NULL, &transform.screenTransform);;
	}
	

	std::shared_ptr<NetworkPacket> ClientActor::GetPacketTransform() const
	{
		auto net = std::make_shared<NetworkPacket>(NETCOMMANDType::Update,ID, transform.Serialize());
		return net;
		
		
		
	}

}
