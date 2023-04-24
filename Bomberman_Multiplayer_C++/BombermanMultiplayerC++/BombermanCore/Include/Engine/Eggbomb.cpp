#include "Eggbomb.h"

namespace Bomberman
{
	
	// SDL_Texture* Eggbomb::currentTexture;
	//Eggbomb::Eggbomb(const Actor* owner) : Actor( "EGGOLD.png")
	//{
	//	
	//	timer = 5;
	//	transform.SetDimensions({ 40, 48 });

	//	//Vector2 owner_center = owner->GetCenter();
	//	T owner_pos = owner->
	//	
	//	SetPosition(owner_pos);
	//	
	//	//Player_ID = player_id;
	//}
	Eggbomb::Eggbomb(const float x,const float y) : Actor("EGGOLD.png")
	{
		timer = 5;
		transform.SetDimensions({ 40, 48 });
		//return;
		//float xOffset = transform.SDL_rect.w * transform.pivot.x;
		//float yOffset = transform.SDL_rect.h * transform.pivot.y;
		//transform.SDL_rect.x = (int)(x - xOffset);
		//transform.SDL_rect.y = (int)(y - yOffset);
		transform.SetPosition({ x,y });
		
	}

	Eggbomb::Eggbomb(const Eggbomb& other)
	{
		timer = other.timer;
		transform = other.transform;
		//SetPosition(other.GetPosition());
		
	}
	/*Eggbomb& Eggbomb::operator=(const Eggbomb& other)
	{

	}*/
	Eggbomb::~Eggbomb()
	{
		std::cout << "CLASS DESTROYED" << std::endl;
		//Actor::~Actor();
	}
	void Eggbomb::Update()
	{
		Actor::Update();
		timer -= BombermanTime::DeltaTime;
		if (timer <= 0)
		{
			UpdateMgr::RemoveItem(this);
			auto eggsplosion = std::make_unique<Eggsplosion*>(new Eggsplosion(transform.GetPosition(), 1.f));
			//Eggsplosion* eggsplosion = new Eggsplosion(GetPosition(), 1.f);

		}
	}
	
}