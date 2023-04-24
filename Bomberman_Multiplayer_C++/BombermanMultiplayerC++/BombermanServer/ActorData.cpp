#include "ActorData.h"
#include "NetworkBase.h"
#include "Map.h"

namespace Bomberman
{


//unsigned char* ActorData::GetPacketTransform()
//{
//	unsigned char to_ret[16];
//	auto byte_id = byteconverter::IntToBytes(NetworkData.networkID);
//	auto byte_cmd = byteconverter::IntToBytes(NetCommand::Update);
//	auto byte_transform = ObjectTransform.Serialize();
//	
//	byteconverter::BytesAppend(to_ret, 16, 0, byte_id,4);
//	byteconverter::BytesAppend(to_ret, 16, 0, byte_id, 4);
//	byteconverter::BytesAppend(to_ret, 16, 0, byte_id, 4);
//	byteconverter::BytesAppend(to_ret, 16, 0, byte_id, 4);
//
//}

ActorData::ActorData(float x, float y, float w, float h)
{
	
	ObjectTransform.SetPosition(x, y);
	ObjectTransform.SetDimensions(w, h);

}
ActorData::ActorData(Transform t)
{
	ObjectTransform = t;


}
std::shared_ptr<SerialData> ActorData::GetPacketAnnounce()
{
	return NULL;
}
std::shared_ptr<SerialData> ActorData::GetPacketDeath()
{
	return NULL;
}
std::shared_ptr<SerialData> ActorData::GetPacketTransform()
{
	return ObjectTransform.Serialize();
}












}