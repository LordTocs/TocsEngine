#pragma once

namespace Tocs {
namespace Math {

class Vector2i 
{
public:
	int X, Y;
	Vector2i();
	Vector2i(int x, int y);
	
	Vector2i & operator () (int x, int y);

	Vector2i &Normalize ();

	int Dot (const Vector2i &op2) const;
	//Vector2 Cross (const Vector2 &op2) const;

	float Length () const;
	float LengthSquared () const;
	float Distance (const Vector2i &op2) const;
	float DistanceSquared (const Vector2i &op2) const;
	bool WithinDistance (const Vector2i &point, float distance) const;

	static int DotProduct (const Vector2i &op1, const Vector2i &op2);
	//static Vector2 CrossProduct (const Vector2 &op1, const Vector2 &op2);

	bool operator== (const Vector2i &op2) const;
	bool operator!= (const Vector2i &op2) const;

	Vector2i &operator+= (const Vector2i &op2);
	Vector2i &operator-= (const Vector2i &op2);
	Vector2i &operator*= (int op2);

};

Vector2i operator- (const Vector2i &op1, const Vector2i &op2);
Vector2i operator+ (const Vector2i &op1, const Vector2i &op2);
Vector2i operator* (const Vector2i &op1, int op2);
Vector2i operator* (int op1, const Vector2i &op2);
Vector2i operator/ (const Vector2i &op1, int op2);
Vector2i Clamp (Vector2i value, Vector2i min, Vector2i max);

}}