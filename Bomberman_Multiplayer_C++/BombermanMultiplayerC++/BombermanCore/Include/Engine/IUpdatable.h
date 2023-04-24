#pragma once
#include "BombermanTime.h"
namespace Bomberman
{

	class IUpdatable
	{
		public:
			//static const float& Delta_Time_ref;
			virtual void Update() = 0;
			
			virtual ~IUpdatable() {};
	};
}
