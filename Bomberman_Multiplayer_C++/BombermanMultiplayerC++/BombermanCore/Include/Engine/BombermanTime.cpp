#pragma once
#include "BombermanTime.h"
namespace Bomberman
{

    Uint64 BombermanTime::currentTime = 0;
    Uint64 BombermanTime::previousTime = 0;

    float BombermanTime::deltaTime = 0;
    float BombermanTime::DeltaTime=0;
    float BombermanTime::FPS = 0;

    BombermanTime::BombermanTime( float DeltaTime)
    {
	    BombermanTime::DeltaTime = DeltaTime;
    }

    float BombermanTime::DeltaTimeUpdate()
    {
        currentTime = SDL_GetPerformanceCounter();
        deltaTime = (float)(currentTime - previousTime) / (float)SDL_GetPerformanceFrequency();
        BombermanTime::DeltaTime = deltaTime;
        previousTime = currentTime;
        float fps = (1.f / deltaTime);
        FPS = fps;
        return fps;
    }
}