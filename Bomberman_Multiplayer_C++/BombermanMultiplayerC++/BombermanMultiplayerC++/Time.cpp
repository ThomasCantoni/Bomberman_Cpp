#include "Time.h"
#pragma once

float Time::DeltaTime=0;

Time::Time( float DeltaTime)
{
	Time::DeltaTime = DeltaTime;
}