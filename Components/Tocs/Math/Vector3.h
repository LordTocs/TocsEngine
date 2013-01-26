#pragma once

namespace Tocs {
namespace Math {

class Vector3
{
public:
	float X, Y, Z;
	Vector3();
	Vector3(float x, float y, float z);
	
	Vector3 & operator () (float x, float y, float z);

	Vector3 &Normalize ();

	float Dot (const Vector3 &op2) const;
	Vector3 Cross (const Vector3 &op2) const;

	float Length () const;
	float LengthSquared () const;
	float Distance (const Vector3 &op2) const;
	float DistanceSquared (const Vector3 &op2) const;
	bool WithinDistance (const Vector3 &point, float distance) const;

	static float DotProduct (const Vector3 &op1, const Vector3 &op2);
	static Vector3 CrossProduct (const Vector3 &op1, const Vector3 &op2);
	static Vector3 Normalized (const Vector3 &vector);

	bool operator== (const Vector3 &op2) const;
	bool operator!= (const Vector3 &op2) const;

	Vector3 &operator+= (const Vector3 &op2);
	Vector3 &operator-= (const Vector3 &op2);
	Vector3 &operator*= (float op2);

};

Vector3 operator- (const Vector3 &op1, const Vector3 &op2);
Vector3 operator+ (const Vector3 &op1, const Vector3 &op2);
Vector3 operator* (const Vector3 &op1, float op2);
Vector3 operator* (float op1, const Vector3 &op2);
Vector3 operator/ (const Vector3 &op1, float op2);

}}