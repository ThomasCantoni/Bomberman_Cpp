#pragma once
#include "Actor.h"
#include "IAttack.h"
#include "NetworkBase.h"

namespace Bomberman
{
	class OnlinePlayer : public Actor
	{
	public:
		Vector2 old_position, latest_position;
		Vector2 current_position;
		int     ID;
		float   lerp_accumulator;

		OnlinePlayer() = delete;
		OnlinePlayer(const int ID);
		OnlinePlayer(const OnlinePlayer& other);
		OnlinePlayer& operator=(const OnlinePlayer& other) = default;

		~OnlinePlayer();
		
		void Update() override;
	};

}