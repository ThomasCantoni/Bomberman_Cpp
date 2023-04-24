#include "Time.h"
#pragma once
namespace Bomberman
{

float Time::DeltaTime=0;

Time::Time( float DeltaTime)
{
	Time::DeltaTime = DeltaTime;
}
}