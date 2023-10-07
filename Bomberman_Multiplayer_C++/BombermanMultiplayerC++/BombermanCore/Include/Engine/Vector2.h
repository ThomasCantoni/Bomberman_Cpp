#pragma once
#include <math.h>

struct Vector2
{

	float x;
	float y;

	/*Vector2 Vec2_towards(Vector2 start, Vector2 end);
	Vector2 Vec2_multiply(Vector2 vector, float coeff);
	Vector2 Vec2_add(Vector2 dest, Vector2 plus);
	float Magnitude(Vector2 vector);
	void Vec2_Normalize(Vector2* ToNormalize);*/
	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator>(const Vector2& other)
	{
		float m1 = this->Magnitude();
		float m2 = other.Magnitude();
		
		return m1 > m2;
	}
	Vector2& operator+(const Vector2& other) const
	{
		Vector2 sum;
		sum.x = x + other.x;
		sum.y = y + other.y;
		return sum;
	}
	Vector2& operator-(const Vector2& other) const
	{
		Vector2 diff;
		diff.x = x- other.x;
		diff.y = y- other.y;
		return diff;
	}
	const Vector2 operator*(const float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}
	const Vector2 operator*(const Vector2& other) const
	{
		float mulx = x * other.x;
		float muly = y * other.y;
		return Vector2(mulx,muly);
	}
	const Vector2 operator/(const Vector2& other) const
	{
		float divx = x / other.x;
		float divy = y / other.y;
		return Vector2(divx, divy);
	}
	 Vector2& operator=(const Vector2& other)
	{
		
		x =  other.x;
		y =  other.y;
		return *this;
	}
	 Vector2& operator+=(const Vector2& other)
	 {

		 x += other.x;
		 y += other.y;
		 return *this;
	 }
		Vector2& operator-=(const Vector2& other)
		{
	
			 x -= other.x;
			 y -= other.y;
			return *this;
		}
	static const Vector2& Zero()
	{
		return  { 0,0};
	}
	static Vector2&& One()
	{
		
		return { 1,1 };
	}
	static Vector2 Vector2_Lerp(Vector2 a, Vector2 b, float coeff)
	{
		float r1 = a.x + (b.x - a.x) * coeff;
		float r2 = a.y + (b.y - a.y) * coeff;
		Vector2 result;
		result.x = r1;
		result.y = r2;
		return result;
	}
	/*Vector2 Vec2_towards(Vector2 start, Vector2 end)
	{
		Vector2 start_to_end;
		start_to_end.x = end.x - start.x;
		start_to_end.y = end.y - start.y;
		return start_to_end;
	}*/
	/*Vector2 Vec2_multiply(Vector2 vector, float coeff)
	{
		Vector2 multiplied;
		multiplied.x = vector.x * coeff;
		multiplied.y = vector.y * coeff;
		return multiplied;
	}
	Vector2 Vec2_add(Vector2 dest, Vector2 plus)
	{
		Vector2 result;
		result.x = dest.x + plus.x;
		result.y = dest.y + plus.y;
		return result;
	}*/
	float Magnitude() const
	{
		return 0 + (float)sqrt((x * x) + (y * y));
	}
	Vector2& Normalize()
	{
		float mag = Magnitude();
		x /= mag;
		y /= mag;
		if (x != x)
		{
			x = 0;
		}
		if (y != y)
		{
			y = 0;
		}
		return *this;
	}

//private:
//	void Normalized2(float* x, float* y);
	
};

     //Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float coeff);

	

