#pragma once
#include <iostream>

namespace Tocs {
namespace Math {

class Vector4
{
public:
	float X,Y,Z,W;

	Vector4() : X(0), Y(0), Z(0), W(0) {}

	Vector4(float x, float y, float z, float w)
		: X(x), Y(y), Z(z), W(w) {}
	
	Vector4 & operator () (float x, float y, float z, float w)
	{ X = x; Y = y; Z = z; W = w; return *this; }

	Vector4 &Normalize ();

	float Dot (const Vector4 &op2) const;

	float Length () const;
	float LengthSquared () const;
	float Distance (const Vector4 &op2) const;
	float DistanceSquared (const Vector4 &op2) const;
	bool WithinDistance (const Vector4 &point, float distance) const;

	static float DotProduct (const Vector4 &op1, const Vector4 &op2);
	static Vector4 Normalized (const Vector4 &vector);

	bool operator== (const Vector4 &op2) const;
	bool operator!= (const Vector4 &op2) const;

	Vector4 &operator+= (const Vector4 &op2);
	Vector4 &operator-= (const Vector4 &op2);
	Vector4 &operator*= (float op2);
	Vector4 &operator/= (float op2);

	float &operator[](int axis)
	{ return *(&X + axis); }
	const float &operator[](int axis) const
	{ return *(&X + axis); }

};

Vector4 operator- (const Vector4 &op1, const Vector4 &op2);
Vector4 operator+ (const Vector4 &op1, const Vector4 &op2);
Vector4 operator* (const Vector4 &op1, float op2);
Vector4 operator* (float op1, const Vector4 &op2);
Vector4 operator/ (const Vector4 &op1, float op2);
std::ostream &operator<< (std::ostream &stream, const Vector4 &vec);
Vector4 Clamp (Vector4 value, Vector4 min, Vector4 max);
}}