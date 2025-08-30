#include "NETPhysicsMgr.h"

namespace Bomberman 
{

	std::list< std::shared_ptr<NETRigidBody> >::iterator  NETPhysicsMgr::iterator;
	std::list< std::shared_ptr<NETRigidBody> >			 NETPhysicsMgr::items;
	std::list< std::shared_ptr<NETRigidBody> >			 NETPhysicsMgr::itemsToRemove;
	NETCollision* NETPhysicsMgr::collisionInfo = new NETCollision();


	void NETPhysicsMgr::AddItem(std::shared_ptr<NETRigidBody>  to_add)
	{
		
		items.push_front(to_add);
	}
	void NETPhysicsMgr::AddItem(NETRigidBody* to_add)
	{
		//items.push_front(to_add.get());
	}
	void NETPhysicsMgr::RemoveItem(std::shared_ptr<NETRigidBody>  to_rem)
	{
		if (RemoveItemContains(to_rem) == false)
			itemsToRemove.push_front(to_rem);
		return;
		//items.remove(to_rem);

		for (auto i = items.begin(); i != items.end(); i++)
		{
			if ((*i) == to_rem)
			{
				iterator = items.erase(i);
				return;
			}
		}
	}
	void NETPhysicsMgr::RemoveItemImmediately(NETRigidBody* to_rem)
	{

		//items.remove(to_rem);

		for (auto i = items.begin(); i != items.end(); i++)
		{
			if ((*i).get() == to_rem)
			{
				
				iterator = items.erase(i);
				return;
			}
		}
	}
	void NETPhysicsMgr::ClearAll()
	{
		items.clear();
	}
	void NETPhysicsMgr::Update()
	{
		//update all items

		iterator = items.begin();
		while (iterator != items.end())
		{
			if ((*iterator) != nullptr)
			{
				(*iterator)->Update();
				if ((*iterator)->Owner->GetID() == 0x1c)
				{
					Vector2 currentPos = (*iterator)->GetPosition();
					std::cout << "PLAYER COORD: " << currentPos.x << " " << currentPos.y << "\n";
				}
			}

			iterator++;
		}
		for (auto i = itemsToRemove.begin(); i != itemsToRemove.end(); i++)
		{

			items.remove((*i));
			//delete* i;

			//free(*i);
		}
		itemsToRemove.clear();
	}
	bool NETPhysicsMgr::ItemContains(std::shared_ptr<NETRigidBody>  toCheck)
	{
		return std::find(items.begin(), items.end(), toCheck) != items.end();
	}
	
	bool NETPhysicsMgr::RemoveItemContains(std::shared_ptr<NETRigidBody>  toCheck)
	{
		return std::find(itemsToRemove.begin(), itemsToRemove.end(), toCheck) != itemsToRemove.end();
		for (auto i = items.begin(); i != items.end(); i++)
		{
			if ((*i) == toCheck)
				return true;
		}

		return false;
	}
	
	
	void NETPhysicsMgr::CheckCollisions()
	{
		int currentItemIndex = 0;
		int itemSize = items.size();
		//collisionInfo =  NETCollision();
		for (auto i = items.begin(); i != items.end(); i++)
		{
			currentItemIndex++;
			if ((*i)->IsActive() && (*i)->IsCollisionsAffected) //&& currentItemIndex++ != itemSize
			{
				//check collisions with next items
				for (auto j = i; j != items.end(); j++)
				{
					if ((*i) == (*j) || ((*i)->IsStatic && (*j)->IsStatic))
						continue; //skip a loop if im checking the same object or if both objects are static

					if ((*j)->IsActive() && (*j)->IsCollisionsAffected)
					{
						//check if one of the RB is interested in collision check
						//Collision temporary = collisionInfo;
						
						bool firstCheck = (*i)->CollisionTypeMatches((*j)->Type);
						bool secondCheck = (*j)->CollisionTypeMatches((*i)->Type);

						if ((firstCheck || secondCheck) && (*i)->Collides((*j), collisionInfo))
						{
							std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
							if (firstCheck)
							{
								collisionInfo->Collider = (*j)->Owner;
								(*i)->Owner->OnCollide(*collisionInfo);
							}

							if (secondCheck)
							{
								collisionInfo->Collider = (*i)->Owner;
								(*j)->Owner->OnCollide(*collisionInfo);
							}
						}
					}
				}
			}
		}
		//delete collisionInfo;
	}
}