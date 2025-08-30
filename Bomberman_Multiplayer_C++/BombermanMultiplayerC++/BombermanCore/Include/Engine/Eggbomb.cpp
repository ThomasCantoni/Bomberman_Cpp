#include "Eggbomb.h"

namespace Bomberman
{
	
	
	Eggbomb::Eggbomb(const float x,const float y) : ClientActor("EGGOLD.png")
	{
		timer = 5;
		transform.SetDimensions({ 40, 48 });
		transform.SetPosition({ x,y });
		
	}

	Eggbomb::Eggbomb(const Eggbomb& other)
	{
		timer = other.timer;
		transform = other.transform;
	
		
	}
	
	Eggbomb::~Eggbomb()
	{
		std::cout << "CLASS DESTROYED" << std::endl;
	
	}
	void Eggbomb::Update()
	{
		ClientActor::Update();
		timer -= BombermanTime::DeltaTime;
		if (timer <= 0)
		{
			UpdateMgr::RemoveItem(this);
			auto eggsplosion = std::make_unique<Eggsplosion*>(new Eggsplosion(transform.GetPosition(), 1.f));
			

		}
	}
	
}