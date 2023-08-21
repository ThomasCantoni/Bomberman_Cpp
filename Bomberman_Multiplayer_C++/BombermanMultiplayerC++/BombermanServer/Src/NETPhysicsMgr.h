#pragma once
#include "NETRigidBody.h"
#include <list>
#include "Vector2.h"
#include "NETCollider.h"
#include "NETCollision.h"
namespace Bomberman {
	class NETPhysicsMgr
	{
	protected:

	public:

		static std::list< NETRigidBody*> items;
		static std::list< NETRigidBody*> itemsToRemove;
		static std::list< NETRigidBody*>::iterator iterator;
		static NETCollision* collisionInfo;
		
		static void AddItem(NETRigidBody* to_add);
		static void AddItem(std::unique_ptr<NETRigidBody> to_add);

		static bool ItemContains(NETRigidBody* to_check);
		static bool ItemContains(std::unique_ptr<NETRigidBody> to_check);

		static bool RemoveItemContains(NETRigidBody* to_check);
		static bool RemoveItemContains(std::unique_ptr<NETRigidBody> to_check);

		static void CheckCollisions();


		static void RemoveItem(NETRigidBody* to_remove);
		static void RemoveItemImmediately(NETRigidBody* to_remove);

		static void Update();
		static void ClearAll();
	};

}