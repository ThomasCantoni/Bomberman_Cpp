#pragma once
#include <list>
#include "Actor.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>

namespace Bomberman
{
	struct TextureStruct
	{
	public:
		SDL_Texture* texture;
		int w, h;
		char* path;
		std::string name;
		TextureStruct(const char* path);
		
	};
	class TextureFactory
	{
	public:
		static std::list<TextureStruct*> textures;

		static TextureStruct* GetTexture(const char* Name);
		static TextureStruct* LoadTexture(const char* path);

		
	};
}