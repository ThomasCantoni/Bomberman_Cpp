#include "UpdateMgr.h"
namespace Bomberman
{
	std::list< IUpdatable*>::iterator UpdateMgr::iterator;

	std::list< IUpdatable*> UpdateMgr::items;
	std::list< IUpdatable*> UpdateMgr::itemsToRemove;

	UpdateMgr::UpdateMgr()
	{

	}

	void UpdateMgr::AddItem( IUpdatable* to_add)
	{
		items.push_front(to_add);
	}
	void UpdateMgr::AddItem( std::unique_ptr<IUpdatable> to_add)
	{
		items.push_front(to_add.get());
	}
	void UpdateMgr::RemoveItem( IUpdatable* to_rem)
	{
		if(RemoveItemContains(to_rem) == false)
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
	void UpdateMgr::RemoveItemImmediately( IUpdatable* to_rem)
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

	void UpdateMgr::ClearAll()
	{
		items.clear();
	}


	void UpdateMgr::Update()
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
			delete *i;
			
			//free(*i);
		}
		itemsToRemove.clear();
	}
	bool UpdateMgr::ItemContains( IUpdatable* toCheck)
	{
		return std::find(items.begin(), items.end(), toCheck) != items.end();
	}
	bool UpdateMgr::ItemContains( std::unique_ptr<IUpdatable> toCheck)
	{
		return ItemContains(toCheck.get());
	}
	bool UpdateMgr::RemoveItemContains( IUpdatable* toCheck)
	{
		return std::find(itemsToRemove.begin(), itemsToRemove.end(), toCheck) != itemsToRemove.end();
		for (auto i = items.begin(); i != items.end(); i++)
		{
			if ((*i) == toCheck)
				return true;
		}

		return false;
	}
	bool UpdateMgr::RemoveItemContains(std::unique_ptr<IUpdatable> toCheck)
	{
		return RemoveItemContains(toCheck.get());
	}

	
}