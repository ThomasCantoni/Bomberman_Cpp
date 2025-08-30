#pragma once
#include "Actor.h"
#include "Eggsplosion.h"

namespace Bomberman
{
	class Eggbomb : public ClientActor
	{
	public: 
	
		
		float timer ;
		Eggbomb() = delete;
		Eggbomb(const float x,const float y);
		Eggbomb(const Eggbomb& other);
		Eggbomb& operator=(const Eggbomb& other) = default;

		~Eggbomb();
		void Update() override;
		
	};
}

