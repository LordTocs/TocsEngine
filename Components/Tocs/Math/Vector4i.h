#pragma once
#include <iostream>
namespace Tocs {
namespace Math {

class Vector4i
{
public:
	int X,Y,Z,W;

	Vector4i() : X(0), Y(0), Z(0), W(0) {}

	Vector4i(int x, int y, int z, int w)
		: X(x), Y(y), Z(z), W(w) {}
	
	Vector4i & operator () (int x, int y, int z, int w)
	{ X = x; Y = y; Z = z; W = w; return *this; }

	int Dot (const Vector4i &op2) const;

	float Length () const;
	float LengthSquared () const;
	float Distance (const Vector4i &op2) const;
	float DistanceSquared (const Vector4i &op2) const;
	bool WithinDistance (const Vector4i &point, int distance) const;

	static int DotProduct (const Vector4i &op1, const Vector4i &op2);

	bool operator== (const Vector4i &op2) const;
	bool operator!= (const Vector4i &op2) const;

	Vector4i &operator+= (const Vector4i &op2);
	Vector4i &operator-= (const Vector4i &op2);
	Vector4i &operator*= (int op2);
	Vector4i &operator/= (int op2);

	int &operator[](int axis)
	{ return *(&X + axis); }
	const int &operator[](int axis) const
	{ return *(&X + axis); }

};

Vector4i operator- (const Vector4i &op1, const Vector4i &op2);
Vector4i operator+ (const Vector4i &op1, const Vector4i &op2);
Vector4i operator* (const Vector4i &op1, int op2);
Vector4i operator* (int op1, const Vector4i &op2);
Vector4i operator/ (const Vector4i &op1, int op2);
std::ostream &operator<< (std::ostream &stream, const Vector4i &vec);

}}