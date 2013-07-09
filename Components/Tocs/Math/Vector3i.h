#pragma once
#include <iostream>
namespace Tocs {
namespace Math {


class Vector3i
{
public:
	int X, Y, Z;
	Vector3i();
	Vector3i(int x, int y, int z);
	
	Vector3i & operator () (int x, int y, int z);

	int Dot (const Vector3i &op2) const;
	Vector3i Cross (const Vector3i &op2) const;

	float Length () const;
	float LengthSquared () const;
	float Distance (const Vector3i &op2) const;
	float DistanceSquared (const Vector3i &op2) const;
	bool WithinDistance (const Vector3i &point, float distance) const;

	static int DotProduct (const Vector3i &op1, const Vector3i &op2);
	static Vector3i CrossProduct (const Vector3i &op1, const Vector3i &op2);

	bool operator== (const Vector3i &op2) const;
	bool operator!= (const Vector3i &op2) const;

	Vector3i &operator+= (const Vector3i &op2);
	Vector3i &operator-= (const Vector3i &op2);
	Vector3i &operator*= (float op2);

};

Vector3i operator- (const Vector3i &op1, const Vector3i &op2);
Vector3i operator+ (const Vector3i &op1, const Vector3i &op2);
Vector3i operator* (const Vector3i &op1, int op2);
Vector3i operator* (int op1, const Vector3i &op2);
Vector3i operator/ (const Vector3i &op1, int op2);
std::ostream &operator<< (std::ostream &stream, const Vector3i &vec);

}}