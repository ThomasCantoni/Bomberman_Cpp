#pragma once
#include "Map.h"
namespace Bomberman
{

class Scene
{
public:
	Map* currentMap;


	Scene(Map* toLoad);

	void OnEnter();
	void OnExit();
};

}
