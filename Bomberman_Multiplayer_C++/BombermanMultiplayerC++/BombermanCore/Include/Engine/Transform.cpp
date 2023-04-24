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
		
		d->Print();
		return d;
	}
}