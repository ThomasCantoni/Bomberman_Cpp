#pragma once
#include "SDL.h"
namespace Bomberman
{

	class BombermanTime
	{
	private:
		static Uint64 currentTime;
		static Uint64 previousTime;
		static float deltaTime;
	public :
		  static  float  DeltaTime ;
		  static float FPS;
		  BombermanTime(float DeltaTime);
		  static float DeltaTimeUpdate();
	};
}

