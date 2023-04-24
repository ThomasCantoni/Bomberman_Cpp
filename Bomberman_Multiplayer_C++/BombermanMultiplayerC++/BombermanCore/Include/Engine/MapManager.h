#pragma once
#include <string>
#include "Map.h"
namespace Bomberman
{

	class MapManager 
	{
	public:
		static int CurrentMapIndex;
		static std::shared_ptr<Map> CurrentMap;
		static std::string map_names[5];
		static void Update();
		static void Initialize(std::string MapFilePath);
		static void LoadMap(int Index);
		static std::string GetMap(int Index);
	};


}