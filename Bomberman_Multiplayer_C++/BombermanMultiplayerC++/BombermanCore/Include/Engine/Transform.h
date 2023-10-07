#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "INetObject.h"

namespace Bomberman
{
	class Transform :public ISerializable
	{
	protected:
		Vector2 virtualPosition;
	public:
		Vector2 pivot;
		SDL_Rect screenTransform;
		
		
		Transform();
		Transform(const Vector2 position, const  Vector2 pivot, const  Vector2 dimensions);
		~Transform() = default;

		Transform& operator=(const Transform& other) = default;
		


		void AddVelocity(const Vector2 toAdd);
		Vector2 GetScreenPosition() const;
		Vector2 GetPosition() const;
		const Vector2 GetUnpivotedPosition();
		void SetPosition(const Vector2 toSet);
		

		const Vector2 GetDimensions() const;
		void SetDimensions(const Vector2 newDimensions);
		void SetDimensions(const float x, const float y);
		const SDL_Rect GetScreenTransform() const;
		
		std::shared_ptr<SerialData> Serialize() const override;
		std::shared_ptr<ISerializable> Deserialize(std::shared_ptr<SerialData>) const override;

	};

}