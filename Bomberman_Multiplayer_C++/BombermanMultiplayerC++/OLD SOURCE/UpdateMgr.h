#pragma once
#include <list>
#include <memory>
#include "IUpdatable.h"
#include <cstdbool>
namespace Bomberman
{

	class UpdateMgr
	{
	protected:
		static std::list< IUpdatable*> items;
		static std::list< IUpdatable*> itemsToRemove;

		static std::list< IUpdatable*>::iterator iterator;

	public:
		UpdateMgr();
		static void AddItem( IUpdatable* to_add);
		static void AddItem( std::unique_ptr<IUpdatable> to_add);

		static bool ItemContains( IUpdatable* to_check);
		static bool ItemContains( std::unique_ptr<IUpdatable> to_check);

		static bool RemoveItemContains( IUpdatable* to_check);
		static bool RemoveItemContains( std::unique_ptr<IUpdatable> to_check);



		static void RemoveItem( IUpdatable* to_remove);
		static void RemoveItemImmediately( IUpdatable* to_remove);

		static void Update() ;
		static void ClearAll()  ;
	};
}

