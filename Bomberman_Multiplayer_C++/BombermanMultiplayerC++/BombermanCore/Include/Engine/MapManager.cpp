#include "MapManager.h"

namespace Bomberman
{
	void MapManager::Initialize(std::string MapFilePath)
	{
		BombermanClientMgr::MapIndexReceived.AddLambda([](int index)
			{
				MapManager::LoadMap(index);
			});

		map_names[0] = "..\\BombermanCore\\Include\\Maps\\map1.txt";
	}
	void MapManager::LoadMap(int index)
	{
		
			//std::list<SDL_Rect> list_to_add;

			std::ifstream my_file;
			my_file.open(map_names[index]);
			if (!my_file.is_open())
			{
				return;
			}
			CurrentMap = std::make_shared<Map>();
			std::string current_line;
			int debug_int = 0;
			while (std::getline(my_file, current_line))
			{
				if (current_line.empty() == true)
					continue;
				int x, y, w, h;
				bool isStatic;
				//size_t current_index,next_index;

				std::vector<std::string> splitted = byteconverter::split(current_line, ',');
				x = stoi(splitted[0]);
				y = stoi(splitted[1]);
				w = stoi(splitted[2]);
				h = stoi(splitted[3]);
				stoi(splitted[4]) > 0 ? isStatic = true : isStatic = false;




				CurrentMap->AddRect({ x,y,w,h }, isStatic);
				debug_int++;

			}
			my_file.close();
			std::cout << debug_int << std::endl;
			
		
	}
	void MapManager::Update()
	{
		CurrentMap->Update();
	}
}