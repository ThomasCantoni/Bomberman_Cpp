#pragma once
#include "RigidBody.h"
#include <list>
#include "Vector2.h"
#include "Collider.h"
namespace Bomberman
{
	class PhysicsMgr
	{
	protected:

	public:

		static std::list< RigidBody*> items;
		static std::list< RigidBody*> itemsToRemove;
		static std::list< RigidBody*>::iterator iterator;
		static Collision* collisionInfo;
		static void AddItem(RigidBody* to_add);
		static void AddItem(std::unique_ptr<RigidBody> to_add);

		static bool ItemContains(RigidBody* to_check);
		static bool ItemContains(std::unique_ptr<RigidBody> to_check);

		static bool RemoveItemContains(RigidBody* to_check);
		static bool RemoveItemContains(std::unique_ptr<RigidBody> to_check);

		static void CheckCollisions();
		

		static void RemoveItem(RigidBody* to_remove);
		static void RemoveItemImmediately(RigidBody* to_remove);

		static void Update();
		static void ClearAll();
	};

}