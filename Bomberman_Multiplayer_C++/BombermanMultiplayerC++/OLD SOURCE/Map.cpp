#include "Map.h"
#include "ColliderFactory.h"
#include <sstream>
#include <fstream>

namespace Bomberman
{
	


	Tile::Tile(SDL_Rect rect,bool isStatic) : Actor()
	{

		transform.SDL_rect = rect;
		rigidbody = new RigidBody(this);
		rigidbody->SetStatic(isStatic);
		rigidbody->friction = Vector2::One() * 2.f;
		rigidbody->Collider = (Collider*)ColliderFactory::CreateBoxFor(this);
		rigidbody->AddCollisionType(RigidBodyType::Player);
		rigidbody->AddCollisionType(RigidBodyType::Wall);

		rigidbody->Type = RigidBodyType::Wall;
	}
	void Tile::Update()
	{
		SDL_RenderFillRect(SDL_Object::renderer, &transform.SDL_rect);
	}


	std::string Map::map_names[5];
	Map::Map() 
	{
		UpdateMgr::AddItem(this);
		map_names[0] = "materials\\Maps\\map1.txt";
	}
	Map::Map( Player* pl) 
	{
		player = pl;
		Map();
	}
	void Map::Update()
	{
		
		
		SDL_Rect target = player->transform.GetRectangle();
		for (auto i = MapGeometry.begin(); i != MapGeometry.end(); i++)
		{
			SDL_SetRenderDrawColor(SDL_Object::renderer, 0x7f,0x82,0x78, 255);
			(*i)->Update();
			SDL_Rect target2 = { player->transform.GetPosition().x,player->transform.GetPosition().y,64,64 };
			SDL_Rect current_rect = (*i)->transform.SDL_rect;
			SDL_RenderFillRect(SDL_Object::renderer, &current_rect);
			continue;
			if (SDL_HasIntersection(&target2, &current_rect))
			{
				if (current_rect.x < target.x)
				{
					player->speedXnegative = 0;
			    }
				if (current_rect.y < target.y)
				{
					player->speedYnegative = 0;
				}
				if (current_rect.x > target.x)
				{
					player->speedX = 0;
				}
				if (current_rect.y > target.y)
				{
					player->speedY = 0;
				}
			}
			else
			{
				player->speedX = 1;
				player->speedY = 1;

				player->speedXnegative = 1;

				player->speedYnegative = 1;

			}
			//continue;
			if (SDL_HasIntersection(&target2, &current_rect))
			{
				int w, h;
				SDL_IntersectRect(&target2, &current_rect, &current_rect);
				w = current_rect.w;
				h = current_rect.h;

				if (w > h)
				{
					if (target2.y < current_rect.y)
					{
						//player->transform.GetPosition().y = current_rect.y - 64; // player->SDL_rect.h;
					}
					else 
					{
						//player->transform.GetPosition().y = current_rect.y +current_rect.h;
					}
					
				}
				else
				{
					if (target2.x < current_rect.x)
					{
						//player->position.x = current_rect.x - 64; // player->SDL_rect.w;
					}
					else
					{
						//player->position.x = current_rect.x + current_rect.w;
					}
				}
			}
			
		}
	}
	void Map::AddRect(const SDL_Rect to_add,bool IsStatic)
	{
		Tile* newTile = new Tile(to_add,IsStatic);
		MapGeometry.push_front(newTile);

	}
	void Map::AddTile( Tile* newTile)
	{
		
		MapGeometry.push_front(newTile);

	}
	/*void Map::RemoveRect(const SDL_Rect* to_rem)
	{
		for (auto i = MapGeometry.begin(); i != MapGeometry.end(); i++)
		{
			if (*i == to_rem)
			{
				delete to_rem;
				SDL_free(to_rem);
				i = MapGeometry.erase(i);
			}
		}
	}*/
	
	Map::~Map() 
	{
		
		MapGeometry.clear();
	}
	std::vector<std::string> split(const std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}
	void Map::BuildMap(int index)
	{
		//std::list<SDL_Rect> list_to_add;
		
		std::ifstream my_file;
		my_file.open(map_names[index]);
		std::string current_line;
		int debug_int = 0;
		while (std::getline(my_file, current_line))
		{
			if (current_line.empty() == true)
				continue;
			int x,y,w,h;
			bool isStatic;
			//size_t current_index,next_index;
			
				std::vector<std::string> splitted = split(current_line, ',');
				x = stoi(splitted[0]);
				y = stoi(splitted[1]);
				w = stoi(splitted[2]);
				h = stoi(splitted[3]);
				stoi(splitted[4]) > 0 ? isStatic = true: isStatic = false;
				
			

			
			AddRect({ x,y,w,h },isStatic);
			debug_int++;
			
		}
		my_file.close();
		std::cout << debug_int << std::endl;
		/*for (auto i = list_to_add.begin(); i != list_to_add.end(); i++)
		{


		}
		return;*/
		
		//list_to_add.push_front({ 1011, 0, 32, 1024  });
		//
		//list_to_add.push_front({ 0, -1, 1012, 30	});
		//list_to_add.push_front({ 0, 738, 1024, 30	});

		//list_to_add.push_front({ 110, 115, 75, 75	}); //left //up //lenght //hight
		//list_to_add.push_front({ 110, 265, 75, 75	});    //////////////////////////////////
		//list_to_add.push_front({ 110, 415, 75, 75	});
		//list_to_add.push_front({ 110, 565, 75, 75	});
		//											 
		//list_to_add.push_front({ 260, 115, 75, 75	});
		//list_to_add.push_front({ 260, 265, 75, 75	});
		//list_to_add.push_front({ 260, 415, 75, 75	});
		//list_to_add.push_front({ 260, 565, 75, 75	});
		//										   
		//list_to_add.push_front({ 410, 115, 75, 75 });
		//list_to_add.push_front({ 410, 265, 75, 75 });
		//list_to_add.push_front({ 410, 415, 75, 75 });
		//list_to_add.push_front({ 410, 565, 75, 75 });
		//										   
		//list_to_add.push_front({ 560, 115, 75, 75 });
		//list_to_add.push_front({ 560, 265, 75, 75 });
		//list_to_add.push_front({ 560, 415, 75, 75 });
		//list_to_add.push_front({ 560, 565, 75, 75 });
		//										   
		//list_to_add.push_front({ 710, 115, 75, 75 });
		//list_to_add.push_front({ 710, 265, 75, 75 });
		//list_to_add.push_front({ 710, 415, 75, 75 });
		//list_to_add.push_front({ 710, 565, 75, 75 });
		//										   
		//list_to_add.push_front({ 860, 115, 75, 75 });
		//list_to_add.push_front({ 860, 265, 75, 75 });
		//list_to_add.push_front({ 860, 415, 75, 75 });
		//list_to_add.push_front({ 860, 565, 75, 75 });
		////AddRect(*list_to_add.begin());
		//for (auto i = list_to_add.begin(); i != list_to_add.end(); i++)
		//{
		//	AddRect(*i);


		//}
		//return;
	}
}