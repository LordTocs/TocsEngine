#include "Quaternion.h"
#include <math.h>

namespace Tocs {
namespace Math {

Quaternion::Quaternion()
	: X(0),Y(0),Z(0),W(1)
{
}

float Quaternion::Magnitude () const
{
	return sqrt (X*X + Y*Y + Z*Z + W*W);
}
Quaternion &Quaternion::Normalize ()
{
	float len = Magnitude ();
	X /= len;
	Y /= len;
	Z /= len;
	W /= len;
	return *this;
}

float Quaternion::Dot (const Quaternion &op2) const
{
	return X * op2.X + Y * op2.Y + Z * op2.Z + W * op2.W;
}

static Quaternion Slerp (const Quaternion &start, const Quaternion &finish, float t)
{
	float theta = acos(start.Dot(finish));
	Quaternion result = start * (sin ((1 - t) * theta)/sin(theta)) + finish * (sin(t * theta)/sin(theta));
	return result;
}
static Quaternion FromEuler (float x, float y, float z)
{
	Quaternion Qx, Qy, Qz;
	Qx.W = cos (x/2);
	Qx.X = sin (x/2);
	Qy.W = cos (y/2);
	Qy.Y = sin (y/2);
	Qz.W = cos (z/2);
	Qz.Z = sin (z/2);
	return Qx * Qy * Qz;
}
static Quaternion FromEuler (const Vector3 &euler)
{
	Quaternion Qx, Qy, Qz;
	Qx.W = cos (euler.X/2);
	Qx.X = sin (euler.X/2);
	Qy.W = cos (euler.Y/2);
	Qy.Y = sin (euler.Y/2);
	Qz.W = cos (euler.Z/2);
	Qz.Z = sin (euler.Z/2);
	return Qx * Qy * Qz;
}

Quaternion operator*(const Quaternion &op1, const Quaternion &op2)
{
	Quaternion result;
	result.W = op1.W*op2.W - op1.X*op2.X - op1.Y*op2.Y - op1.Z*op2.Z;
	result.X = op1.W*op2.X + op1.X*op2.W + op1.Y*op2.Z - op1.Z*op2.Y;
	result.Y = op1.W*op2.Y + op1.Y*op2.W + op1.Z*op2.X - op1.X*op2.Z;
	result.Z = op1.W*op2.Z + op1.Z*op2.W + op1.X*op2.Y - op1.Y*op2.X;
	return result;
}
Quaternion operator*(float op1, const Quaternion &op2)
{
	Quaternion result;
	result.W = op2.W * op1;
	result.X = op2.X * op1;
	result.Y = op2.Y * op1;
	result.Z = op2.Z * op1;
	return result;
}
Quaternion operator*(const Quaternion &op1, float op2)
{
	Quaternion result;
	result.W = op2 * op1.W;
	result.X = op2 * op1.X;
	result.Y = op2 * op1.Y;
	result.Z = op2 * op1.Z;
	return result;
}
Quaternion operator/(const Quaternion &op1, float op2)
{
	Quaternion result;
	result.W = op1.W / op2;
	result.X = op1.X / op2;
	result.Y = op1.Y / op2;
	result.Z = op1.Z / op2;
	return result;
}
Quaternion operator+(const Quaternion &op1, const Quaternion &op2)
{
	Quaternion result;
	result.W = op1.W + op2.W;
	result.X = op1.X + op2.X;
	result.Y = op1.Y + op2.Y;
	result.Z = op1.Z + op2.Z;
	return result;
}
Quaternion operator-(const Quaternion &op1, const Quaternion &op2)
{
	Quaternion result;
	result.W = op1.W - op2.W;
	result.X = op1.X - op2.X;
	result.Y = op1.Y - op2.Y;
	result.Z = op1.Z - op2.Z;
	return result;
}


}}