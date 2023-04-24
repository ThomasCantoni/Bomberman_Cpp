#include "BombermanTime.h"
#pragma once
namespace Bomberman
{

float BombermanTime::DeltaTime=0;

BombermanTime::BombermanTime( float DeltaTime)
{
	BombermanTime::DeltaTime = DeltaTime;
}
}