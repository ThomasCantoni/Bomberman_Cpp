#pragma once
#include "OnlinePlayer.h"
#include <iostream>
namespace Bomberman
{
	OnlinePlayer::OnlinePlayer(const int id) : ClientActor( "materials\\paperella.png")
	{
		
		
		latest_position = { 0,0 };
		old_position = { 0,0 };
		lerp_accumulator = 0;
		ID = id;
		
		
	}

	void OnlinePlayer::Update() 
	{ 
		ClientActor::Update();
		//std::cout << " POSITIONS : " << old_position.x << " " << old_position.y << std::endl;

		lerp_accumulator += BombermanTime::DeltaTime *  (1.f / NETWORK_PERIOD);
		current_position = Vector2::Vector2_Lerp(old_position, latest_position,lerp_accumulator);
		//std::cout <<" POSITIONS : " << old_position.x << " " << old_position.y << std::endl;
		transform.SetPosition({ current_position.x, current_position.y });
		transform.SetDimensions( 64, 64 );
		//SDL_RenderCopy(SDL_Obj->renderer, texture, NULL, &this->SDL_rect);
	}
	OnlinePlayer::OnlinePlayer(const OnlinePlayer& other)
	{
		old_position		= other.old_position	  ;
		latest_position		= other.latest_position   ;
		current_position	= other.current_position  ;
		ID					= other.ID				  ;
		lerp_accumulator	= other.lerp_accumulator  ;
												  
	}
	/*OnlinePlayer& OnlinePlayer::operator=(const OnlinePlayer& other)
	{
		old_position = other.old_position;
		latest_position = other.latest_position;
		current_position = other.current_position;
		ID = other.ID;
		lerp_accumulator = other.lerp_accumulator;

	}*/
	OnlinePlayer::~OnlinePlayer()
	{
		

	}
	
}