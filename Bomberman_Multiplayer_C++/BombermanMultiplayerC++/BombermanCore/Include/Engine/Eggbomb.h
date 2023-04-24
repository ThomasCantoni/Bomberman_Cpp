#pragma once
#include "Actor.h"
#include "Eggsplosion.h"

namespace Bomberman
{
	class Eggbomb : public Actor
	{
	public: 
	
		//static SDL_Texture* currentTexture;
		//int Player_ID=0;
		float timer ;
		Eggbomb() = delete;
		//Eggbomb(SDL_Object* SDL_O, int player_ID);
		//Eggbomb(const Actor* owner);
		Eggbomb(const float x,const float y);
		Eggbomb(const Eggbomb& other);
		Eggbomb& operator=(const Eggbomb& other) = default;

		~Eggbomb();
		void Update() override;
		
	};
}

