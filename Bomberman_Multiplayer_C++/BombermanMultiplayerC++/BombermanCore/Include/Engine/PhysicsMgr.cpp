#include "PhysicsMgr.h"

namespace Bomberman
{
	std::list< RigidBody*>::iterator PhysicsMgr::iterator;
	std::list< RigidBody*>			 PhysicsMgr::items;
	std::list< RigidBody*>			 PhysicsMgr::itemsToRemove;
	Collision* PhysicsMgr::collisionInfo;


	void PhysicsMgr::AddItem(RigidBody* to_add)
	{
		items.push_front(to_add);
	}
	void PhysicsMgr::AddItem(std::unique_ptr<RigidBody> to_add)
	{
		items.push_front(to_add.get());
	}
	void PhysicsMgr::RemoveItem(RigidBody* to_rem)
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
	void PhysicsMgr::RemoveItemImmediately(RigidBody* to_rem)
	{

		//items.remove(to_rem);

		for (auto i = items.begin(); i != items.end(); i++)
		{
			if ((*i) == to_rem)
			{
				delete(*i);
				iterator = items.erase(i);
				return;
			}
		}
	}
	void PhysicsMgr::ClearAll()
	{
		items.clear();
	}
	void PhysicsMgr::Update()
	{
		//update all items

		iterator = items.begin();
		while (iterator != items.end())
		{
			if ((*iterator) != nullptr)
				(*iterator)->Update();

			iterator++;
		}
		for (auto i = itemsToRemove.begin(); i != itemsToRemove.end(); i++)
		{

			items.remove((*i));
			delete* i;

			//free(*i);
		}
		itemsToRemove.clear();
	}
	bool PhysicsMgr::ItemContains(RigidBody* toCheck)
	{
		return std::find(items.begin(), items.end(), toCheck) != items.end();
	}
	bool PhysicsMgr::ItemContains(std::unique_ptr<RigidBody> toCheck)
	{
		return ItemContains(toCheck.get());
	}
	bool PhysicsMgr::RemoveItemContains(RigidBody* toCheck)
	{
		return std::find(itemsToRemove.begin(), itemsToRemove.end(), toCheck) != itemsToRemove.end();
		for (auto i = items.begin(); i != items.end(); i++)
		{
			if ((*i) == toCheck)
				return true;
		}

		return false;
	}
	bool PhysicsMgr::RemoveItemContains(std::unique_ptr<RigidBody> toCheck)
	{
		return RemoveItemContains(toCheck.get());
	}

	 void PhysicsMgr::CheckCollisions()
	{
		 int currentItemIndex = 0;
		 int itemSize = items.size();
		 collisionInfo = new Collision();
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

						bool firstCheck  = (*i)->CollisionTypeMatches((*j)->Type);
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
		delete collisionInfo;
	}
}