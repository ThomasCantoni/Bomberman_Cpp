#include "Transform.h"
namespace Bomberman
{
	Transform::Transform()
	{
		screenTransform = { 0,0,0,0 };
		virtualPosition = { 0,0 };
		pivot = { 0,0 };


	}
	Transform::Transform(const Vector2 position, const  Vector2 pivot, const  Vector2 dimensions)
	{

		Transform::pivot = pivot;
		SetDimensions(dimensions);
		SetPosition(position);


	}
	void Transform::AddVelocity(const Vector2 toAdd)
	{
		//Vector2 previousPos = { SDL_rect.x,SDL_rect.y };
		virtualPosition += toAdd;
		screenTransform.x = (int)virtualPosition.x;
		screenTransform.y = (int)virtualPosition.y;
		//return previousPos;
	}
	Vector2 Transform::GetScreenPosition() const
	{
		return Vector2(screenTransform.x, screenTransform.y);
		Vector2 center;
		center.x = (screenTransform.x + floor(screenTransform.w * pivot.x));
		center.y = (screenTransform.y + floor(screenTransform.h * pivot.y));
		return center;

	}
	Vector2 Transform::GetPosition() const
	{
		Vector2 offset = Vector2(screenTransform.w * pivot.x, screenTransform.h * pivot.y);
		return virtualPosition + offset;
	}
	const Vector2 Transform::GetUnpivotedPosition()
	{
		return virtualPosition;

	}
	void Transform::SetPosition(const Vector2 toSet)
	{
		Vector2 offset = Vector2(screenTransform.w * pivot.x, screenTransform.h * pivot.y);
		virtualPosition = toSet-offset;
		screenTransform.x = (int)virtualPosition.x;
		screenTransform.y = (int)virtualPosition.y;
	}
	

	const Vector2 Transform::GetDimensions() const
	{
		return { (float)screenTransform.w,(float)screenTransform.h };

	}
	void Transform::SetDimensions(const Vector2 newDimensions)
	{
		screenTransform.w = (int)newDimensions.x;
		screenTransform.h = (int)newDimensions.y;
	}
	void Transform::SetDimensions(const float x, const float y)
	{
		Transform::SetDimensions({ x,y });
	}
	const SDL_Rect Transform::GetScreenTransform() const
	{

		SDL_Rect pivotedRect = screenTransform;
		pivotedRect.x += (int)(screenTransform.w * pivot.x);
		pivotedRect.y += (int)(screenTransform.h * pivot.y);

		return  pivotedRect;

	}

	std::shared_ptr<SerialData> Transform::Serialize() const 
	{
		

		Vector2 pos = GetPosition();
		Vector2 dim = GetDimensions();
		
		auto  d = std::make_shared<SerialData>(16);
		// 64 represented in float bytes
		// EXPECTED = 0x80 0x43 
		ByteConverter::BytesAppend(d->data, 0, pos.x);
		ByteConverter::BytesAppend(d->data, 4, pos.y);		   
		ByteConverter::BytesAppend(d->data, 8, dim.x);
		ByteConverter::BytesAppend(d->data, 12,dim.y);
		
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
		pos.x = ByteConverter::BytesToInt(d->data, 0);
		pos.y = ByteConverter::BytesToInt(d->data,  4);
		dim.x = ByteConverter::BytesToInt(d->data, 8);
		dim.y = ByteConverter::BytesToInt(d->data, 12);

		toReturn->SetPosition(pos);
		toReturn->SetDimensions(dim);

		return toReturn;
	}
}