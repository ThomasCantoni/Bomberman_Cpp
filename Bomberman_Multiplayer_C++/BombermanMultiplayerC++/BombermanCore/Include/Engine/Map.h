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
	public:
		
		Tile(const float x, const float y, const float w, const float h,const bool IsStatic=true);

		Tile(SDL_Rect origin,const bool isStatic = true);
		~Tile() = default;
		void Update() override;
	};

class Map : public IUpdatable
{

public:
	
	std::list< Tile*> MapGeometry;
	//std::list<SDL_Rect>::iterator map_iterator;
	//Player* player;
	Map();
	//Map( Player* player);
	~Map() override;

	void AddRect(const SDL_Rect to_add,bool isStatic = true);
	void AddTile(Tile* to_add);

	//void RemoveRect(const SDL_Rect* to_rem);

	void Update() override;
	void BuildMap(int index);
};
}

