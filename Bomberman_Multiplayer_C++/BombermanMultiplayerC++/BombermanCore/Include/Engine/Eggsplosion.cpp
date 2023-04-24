#include "Eggsplosion.h"

namespace Bomberman
{

	Eggsplosion::Eggsplosion() : Actor("eggsplosion.png")
	{

	}
	Eggsplosion::Eggsplosion(const Vector2 position,const float timer) : Actor("eggsplosion.png")
	{
		transform.SetDimensions(150, 150);
		transform.SetPosition(position);
		kill_time = timer;
		
	}
	void Eggsplosion::Update()
	{
		Actor::Update();
		kill_time -= BombermanTime::DeltaTime;
		if (kill_time <= 0)
		{
			UpdateMgr::RemoveItem(this);
		}
	}
}