#include "Transform.h"
namespace Bomberman
{
	
	std::shared_ptr<SerialData> Transform::Serialize() const 
	{
		

		Vector2 pos = GetPosition();
		Vector2 dim = GetDimensions();
		
		auto  d = std::make_shared<SerialData>(16);
		// 64 represented in float bytes
		// EXPECTED = 0x80 0x43 
		byteconverter::BytesAppend(d->data,d->length, 0, pos.x);
		byteconverter::BytesAppend(d->data,d->length, 4, pos.y);
										   
		byteconverter::BytesAppend(d->data,d->length, 8, dim.x);
		byteconverter::BytesAppend(d->data,d->length, 12,dim.y);
		
		//d->Print();
		return d;
	}
	
	
	std::shared_ptr<ISerializable> Transform::Deserialize(std::shared_ptr<SerialData> d) const
	{

		std::shared_ptr<Transform> toReturn;
		Vector2 pos = {};
		Vector2 dim = {};

		// 64 represented in float bytes
		// EXPECTED = 0x80 0x43 
		pos.x = byteconverter::BytesToInt(d->data, 0);
		pos.y = byteconverter::BytesToInt(d->data,  4);
		dim.x = byteconverter::BytesToInt(d->data, 8);
		dim.y = byteconverter::BytesToInt(d->data, 12);

		toReturn->SetPosition(pos);
		toReturn->SetDimensions(dim);

		return toReturn;
	}
}