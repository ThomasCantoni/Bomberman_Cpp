#pragma once
#include "SDL.h"
#include "Vector2.h"
#include "INetObject.h"

namespace Bomberman
{
	class Transform :public ISerializable
	{
	protected:
	public:
		
		SDL_Rect SDL_rect;
		Vector2 pivot;

		Transform() 
		{	
			SDL_rect = { 0,0,0,0 };
			
			pivot = { 0,0 };
			

		}
		Transform(const Vector2 position, const  Vector2 pivot, const  Vector2 dimensions)
		{
			
			Transform::pivot = pivot;
			SDL_rect = { 
				(int)position.x,
				(int)position.y,
				(int)dimensions.x,
				(int)dimensions.y
			};
			
		}
		~Transform() = default;

		Transform& operator=(const Transform& other) = default;
		


		void AddVelocity(const Vector2 toAdd)
		{
			//Vector2 previousPos = { SDL_rect.x,SDL_rect.y };
			SDL_rect.x	+= (int)toAdd.x;
			SDL_rect.y	+= (int)toAdd.y;
			//return previousPos;
		}
		const Vector2 GetPosition() const
		{
			Vector2 center;
			center.x = SDL_rect.x + SDL_rect.w * pivot.x;
			center.y = SDL_rect.y + SDL_rect.h * pivot.y;
			return center;
			//return { SDL_rect.x,SDL_rect.y };
			
		}
		const Vector2 GetUnpivotedPosition()
		{
			Vector2 center;
			center.x =(float)SDL_rect.x ;
			center.y =(float)SDL_rect.y ;
			return center;
			//return { SDL_rect.x,SDL_rect.y };

		}
		void SetPosition(const Vector2 toSet)
		{
			
			float xOffset = SDL_rect.w * pivot.x;
			float yOffset = SDL_rect.h * pivot.y;
			SDL_rect.x = (int)(toSet.x -xOffset);
			SDL_rect.y = (int)(toSet.y -yOffset);
		}
		void SetPosition(const float x,const float y)
		{
			SetPosition({ x,y });
		}
		const Vector2 GetDimensions() const
		{
			return { (float)SDL_rect.w,(float)SDL_rect.h };

		}
		void SetDimensions(const Vector2 newDimensions)
		{
			SDL_rect.w = (int)newDimensions.x;
			SDL_rect.h = (int)newDimensions.y;
		}
		void SetDimensions(const float x,const float y)
		{
			SetDimensions({ x,y });
		}
		const SDL_Rect GetRectangle() const
		{
			
			SDL_Rect pivotedRect = SDL_rect;
			pivotedRect.x +=(int)( SDL_rect.w * pivot.x);
			pivotedRect.y +=(int)( SDL_rect.h * pivot.y);

			return  pivotedRect;

		}
		std::shared_ptr<SerialData> Serialize() const override;
		
	};

}