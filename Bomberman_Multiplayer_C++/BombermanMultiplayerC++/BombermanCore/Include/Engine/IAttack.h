#pragma once

//#include "Time.h"
#include "Eggbomb.h"
#include "Vector2.h"

namespace Bomberman
{

	class IAttack
	{
	public:
		
		virtual void InstantiateEgg(const Vector2 pos) = 0;
		

	};
}