#pragma once
#include "SDL.h"
#include <stdio.h>
#include <iostream>

namespace Bomberman
{

	class SDL_Object
	{
	public:
		static SDL_Window* window;
		static SDL_Renderer* renderer;
		


		SDL_Object()
		{
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
			{
				SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

			}

			window = SDL_CreateWindow("SDL is active!", 100, 100, 1044, 768, 0);
			if (!window)
			{
				SDL_Log("Unable to create window: %s", SDL_GetError());
				SDL_Quit();

			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!renderer)
			{
				SDL_Log("Unable to create renderer: %s", SDL_GetError());
				SDL_DestroyWindow(window);
				SDL_Quit();
				exit(-1);
			}

			//Keys = SDL_GetKeyboardState(NULL);
			puts("COMPLETED");
		}
		~SDL_Object() {
			std::cout << "DESTROYED PROPERLY" << std::endl;
		}


		void StartFrameUpdate()
		{
			SDL_SetRenderDrawColor(renderer, 0x04, 0x52, 0x19, 255);


			SDL_RenderClear(renderer);

		}
		void EndFrameUpdate()
		{

			SDL_RenderPresent(renderer);
		}
	};
}

