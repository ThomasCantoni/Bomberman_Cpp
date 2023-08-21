#pragma once
#include "BombermanTime.h"
namespace Bomberman
{

	class IUpdatable
	{
		public:
			virtual void Update() = 0;
			virtual ~IUpdatable() {};
	};
}
