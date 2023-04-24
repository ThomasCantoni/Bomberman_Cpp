#pragma once
#include "Actor.h"
namespace Bomberman
{
	class Eggsplosion : public Actor

	{
	public:
		float kill_time;

		Eggsplosion();
		Eggsplosion(const Vector2 position, const float timer);
		void Update() override;
	};
}
