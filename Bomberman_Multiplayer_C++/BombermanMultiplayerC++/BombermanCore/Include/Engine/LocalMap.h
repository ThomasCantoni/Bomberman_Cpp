#pragma once
#include <list>
#include "SDL.h"
#include "Actor.h"
#include "Player.h"
#include <sstream>
#include <fstream>

namespace Bomberman
{
	class Tile : public Actor
	{
	private:
		bool isStatic = false;
	public:
		
		Tile(const float x, const float y, const float w, const float h,const bool IsStatic=true);
		Tile(SDL_Rect origin,const bool isStatic = true);
		~Tile() = default;
		void Update() override;
	};

	class Map : public IUpdatable
	{
	public:
		std::list<std::shared_ptr<Tile>> MapGeometry;
		Map();
		~Map() override;
		void AddRect(const SDL_Rect to_add,bool isStatic = true);
		
		void AddTile(std::shared_ptr<Tile> to_add);

		void Update() override;
		void BuildMap(int index);
	};
}

