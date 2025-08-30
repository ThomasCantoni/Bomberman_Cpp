#pragma once
#include "NETRigidBody.h"
#include <list>
#include "Engine/Vector2.h"
#include "NETCollider.h"
#include "NETCollision.h"
namespace Bomberman {
	class NETPhysicsMgr
	{
	protected:

	public:
		
		static std::list<std::shared_ptr<NETRigidBody> > items;
		static std::list<std::shared_ptr<NETRigidBody> > itemsToRemove;
		static std::list<std::shared_ptr<NETRigidBody> >::iterator iterator;
		static NETCollision* collisionInfo;
		
		static void AddItem(std::shared_ptr<NETRigidBody>  to_add);
		static void AddItem(NETRigidBody* to_add);

		static bool ItemContains(std::shared_ptr<NETRigidBody>  to_check);
		static bool ItemContains(NETRigidBody* to_check);

		static bool RemoveItemContains(std::shared_ptr<NETRigidBody>  to_check);
		static bool RemoveItemContains(NETRigidBody* to_check);

		static void CheckCollisions();


		static void RemoveItem(std::shared_ptr<NETRigidBody> to_remove);
		static void RemoveItemImmediately(NETRigidBody* to_remove);

		static void Update();
		static void ClearAll();
	};

}