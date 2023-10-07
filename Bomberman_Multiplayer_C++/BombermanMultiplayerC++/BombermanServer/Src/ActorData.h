#pragma once
#include "Engine/Vector2.h"
//#include "Engine/INetObject.h"
#include "Transform.h"

//#include "NetworkBase.h"
namespace Bomberman
{
	class Tile;
	class NETCollision;
	class NETRigidBody;
class ActorData
{
public:
	Transform ObjectTransform;
	NETRigidBody* rigidbody;
	ActorData() = default;

	ActorData(float x,float y,float w,float h);
	ActorData(Transform t);

	std::shared_ptr<SerialData> GetPacketTransform();
	std::shared_ptr<SerialData> GetPacketAnnounce();
	std::shared_ptr<SerialData> GetPacketDeath();

	virtual void OnCollide(NETCollision& collisionInfo);
	virtual void OnCollideWithStatic(NETCollision& collisionInfo);
	virtual void OnCollideWithDynamic(NETCollision& collisionInfo);
	virtual int GetID();
		

		
};
}

