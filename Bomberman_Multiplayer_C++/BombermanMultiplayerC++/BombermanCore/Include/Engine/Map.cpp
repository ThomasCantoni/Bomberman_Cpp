#include "Map.h"
#include "ColliderFactory.h"


namespace Bomberman
{
	
	Tile::Tile(const float x, const float y, const float w, const float h,const bool isStatic ) : Actor()
	{
		SDL_Rect rect{ x,y,w,h };
		transform.SDL_rect = rect;
		rigidbody = new RigidBody(this);
		rigidbody->SetStatic(isStatic);
		rigidbody->friction = Vector2::One() * 2.f;
		rigidbody->Collider = (Collider*)ColliderFactory::CreateBoxFor(this);
		rigidbody->AddCollisionType(RigidBodyType::Player);
		rigidbody->AddCollisionType(RigidBodyType::Wall);
		
		rigidbody->Type = RigidBodyType::Wall;
	}

	Tile::Tile(SDL_Rect rect,const bool isStatic) : Actor()
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


	
	Map::Map() 
	{
		UpdateMgr::AddItem(this);
		
	}
	
	void Map::Update()
	{
		
		
	
		for (auto i = MapGeometry.begin(); i != MapGeometry.end(); i++)
		{
			SDL_SetRenderDrawColor(SDL_Object::renderer, 0x7f,0x82,0x78, 255);
			(*i)->Update();
			
			SDL_Rect current_rect = (*i)->transform.SDL_rect;
			SDL_RenderFillRect(SDL_Object::renderer, &current_rect);
			continue;
			//if (SDL_HasIntersection(&target2, &current_rect))
			//{
			//	if (current_rect.x < target.x)
			//	{
			//		player->speedXnegative = 0;
			//    }
			//	if (current_rect.y < target.y)
			//	{
			//		player->speedYnegative = 0;
			//	}
			//	if (current_rect.x > target.x)
			//	{
			//		player->speedX = 0;
			//	}
			//	if (current_rect.y > target.y)
			//	{
			//		player->speedY = 0;
			//	}
			//}
			//else
			//{
			//	player->speedX = 1;
			//	player->speedY = 1;
			//	player->speedXnegative = 1;
			//	player->speedYnegative = 1;
			//}
			////continue;
			//if (SDL_HasIntersection(&target2, &current_rect))
			//{
			//	int w, h;
			//	SDL_IntersectRect(&target2, &current_rect, &current_rect);
			//	w = current_rect.w;
			//	h = current_rect.h;
			//	if (w > h)
			//	{
			//		if (target2.y < current_rect.y)
			//		{
			//			//player->transform.GetPosition().y = current_rect.y - 64; // player->SDL_rect.h;
			//		}
			//		else 
			//		{
			//			//player->transform.GetPosition().y = current_rect.y +current_rect.h;
			//		}
			//		
			//	}
			//	else
			//	{
			//		if (target2.x < current_rect.x)
			//		{
			//			//player->position.x = current_rect.x - 64; // player->SDL_rect.w;
			//		}
			//		else
			//		{
			//			//player->position.x = current_rect.x + current_rect.w;
			//		}
			//	}
			//}
			//
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
	
	
}