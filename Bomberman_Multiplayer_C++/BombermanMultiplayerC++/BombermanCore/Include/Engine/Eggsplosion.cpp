#include "Eggsplosion.h"

namespace Bomberman
{

	Eggsplosion::Eggsplosion() : ClientActor("eggsplosion.png")
	{

	}
	Eggsplosion::Eggsplosion(const Vector2 position,const float timer) : ClientActor("eggsplosion.png")
	{
		transform.SetDimensions(150, 150);
		transform.SetPosition(position);
		kill_time = timer;
		
	}
	void Eggsplosion::Update()
	{
		ClientActor::Update();
		kill_time -= BombermanTime::DeltaTime;
		if (kill_time <= 0)
		{
			UpdateMgr::RemoveItem(this);
		}
	}
}