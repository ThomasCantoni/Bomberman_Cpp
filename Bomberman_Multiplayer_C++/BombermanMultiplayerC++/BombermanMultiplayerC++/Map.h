#pragma once
#include <list>
#include "SDL.h"
#include "Actor.h"
#include "Player.h"


namespace Bomberman
{
	class Tile : public Actor
	{
	public:
		
		
		Tile(SDL_Rect origin,bool isStatic = true);
		~Tile() = default;
		void Update() override;
	};

class Map : public IUpdatable
{
public:
	static std::string map_names[5];
	std::list< Tile*> MapGeometry;
	//std::list<SDL_Rect>::iterator map_iterator;
	 Player* player;
	Map();
	Map( Player* player);
	~Map() override;

	void AddRect(const SDL_Rect to_add,bool isStatic = true);
	void AddTile(Tile* to_add);

	//void RemoveRect(const SDL_Rect* to_rem);

	void Update() override;
	void BuildMap(int index);
};
}

