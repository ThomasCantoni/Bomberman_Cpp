#pragma once
#include "TextureFactory.h"
namespace Bomberman
{

	TextureStruct::TextureStruct(const char* path)
	{
		
		path = path;
		std::string nameStr = path;
		size_t index = nameStr.find_last_of('\\');
		int nameLength = nameStr.length() - index;
		name = nameStr.substr(index+1, nameLength);
	}



std::list<TextureStruct*> TextureFactory::textures;

	TextureStruct* TextureFactory::LoadTexture(const char* path)
	{
		
		SDL_Surface* pixels = IMG_Load(path);
		if (!pixels)
		{
			SDL_Log("Unable to open image");
			SDL_DestroyRenderer(SDL_Object::renderer);
			SDL_DestroyWindow(SDL_Object::window);
			SDL_Quit();
			exit(-1);
		}

		SDL_Log("Image width: %d height: %d", pixels->w, pixels->h);
		SDL_Texture* texture = SDL_CreateTexture(SDL_Object::renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, pixels->w, pixels->h);
		//texture = SDL_CreateTextureFromSurface(SDL_Object::renderer, pixels);
		if (!texture)
		{
			SDL_Log("Unable to create texture: %s", SDL_GetError());
			SDL_free(pixels);
			SDL_DestroyRenderer(SDL_Object::renderer);
			SDL_DestroyWindow(SDL_Object::window);
			SDL_Quit();

		}
		//SDL_Texture& tex = *texture;
		TextureStruct* textureStr = new TextureStruct(path);
		
		textureStr->texture = texture;
		textureStr->w = pixels->w;
		textureStr->h = pixels->h;
		textures.push_front(textureStr);
		
		SDL_UpdateTexture(texture, NULL, pixels->pixels, pixels->w * 4);

		SDL_SetTextureAlphaMod(texture, 255);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_FreeSurface(pixels);
		return textureStr;
	}

	TextureStruct* TextureFactory::GetTexture(const char* name)
	{
		std::string compare1 = name;
		for (auto i = textures.begin(); i != textures.end(); ++i)
		{
			std::string compare2 = (*i)->name;
  			if (compare1.compare(compare2) == 0)
			{
				return (*i);
			}
		}
		
		return nullptr;
	}
}
