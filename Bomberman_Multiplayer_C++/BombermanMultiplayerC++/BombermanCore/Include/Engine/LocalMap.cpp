#include "LocalMap.h"



namespace Bomberman
{
	//std::shared_ptr<RigidBody> rigidbody;
	Tile::Tile(const float x, const float y, const float w, const float h,const bool isStatic ) : ClientActor()
	{
		
		transform.SetDimensions(Vector2(w, h));
		transform.SetPosition(Vector2(x, y));

		Tile::isStatic = isStatic;
		/*rigidbody = std::make_shared<RigidBody>(this);
		rigidbody->SetStatic(isStatic);
		rigidbody->friction = Vector2::One() * 2.f;
		rigidbody->Collider = (Collider*)ColliderFactory::CreateBoxFor(this);
		rigidbody->AddCollisionType(RigidBodyType::Player);
		rigidbody->AddCollisionType(RigidBodyType::Wall);*/
		
		//rigidbody->Type = RigidBodyType::Wall;
	}

	Tile::Tile(SDL_Rect rect,const bool isStatic) : ClientActor()
	{

		transform.screenTransform = rect;
		Tile::isStatic = isStatic;
		//rigidbody = new RigidBody(this);
		//rigidbody->SetStatic(isStatic);
		//rigidbody->friction = Vector2::One() * 2.f;
		//rigidbody->Collider = (Collider*)ColliderFactory::CreateBoxFor(this);
		//rigidbody->AddCollisionType(RigidBodyType::Player);
		//rigidbody->AddCollisionType(RigidBodyType::Wall);
		//
		//rigidbody->Type = RigidBodyType::Wall;
	}
	void Tile::Update()
	{
		SDL_RenderFillRect(SDL_Object::renderer, &transform.screenTransform);
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
			
			SDL_Rect current_rect = (*i)->transform.screenTransform;
			SDL_RenderFillRect(SDL_Object::renderer, &current_rect);
			continue;
			
		}
	}
	void Map::AddRect(const SDL_Rect to_add,bool IsStatic)
	{
		auto newTile = std::make_shared<Tile>(to_add,IsStatic);
		MapGeometry.push_front(newTile);

	}
	
	void Map::AddTile(std::shared_ptr<Tile> newTile)
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