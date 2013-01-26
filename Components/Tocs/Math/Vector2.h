#pragma once

namespace Tocs {
namespace Math {

class Vector2 
{
public:
	float X, Y;
	Vector2();
	Vector2(float x, float y);
	
	Vector2 & operator () (float x, float y);

	Vector2 &Normalize ();

	float Dot (const Vector2 &op2) const;
	//Vector2 Cross (const Vector2 &op2) const;

	float Length () const;
	float LengthSquared () const;
	float Distance (const Vector2 &op2) const;
	float DistanceSquared (const Vector2 &op2) const;
	bool WithinDistance (const Vector2 &point, float distance) const;

	static float DotProduct (const Vector2 &op1, const Vector2 &op2);
	//static Vector2 CrossProduct (const Vector2 &op1, const Vector2 &op2);
	static Vector2 Normalized (const Vector2 &vector);

	bool operator== (const Vector2 &op2) const;
	bool operator!= (const Vector2 &op2) const;

	Vector2 &operator+= (const Vector2 &op2);
	Vector2 &operator-= (const Vector2 &op2);
	Vector2 &operator*= (float op2);

};

Vector2 operator- (const Vector2 &op1, const Vector2 &op2);
Vector2 operator+ (const Vector2 &op1, const Vector2 &op2);
Vector2 operator* (const Vector2 &op1, float op2);
Vector2 operator* (float op1, const Vector2 &op2);
Vector2 operator/ (const Vector2 &op1, float op2);

}}