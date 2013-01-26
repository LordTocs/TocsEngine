#include "Vector3.h"
#include <math.h>

namespace Tocs {
namespace Math {

Vector3::Vector3()
	: X (0),
	  Y (0),
	  Z (0)
{}

Vector3::Vector3 (float x, float y, float z)
	: X (x),
	  Y (y),
	  Z (z)
{}

Vector3 &Vector3::operator () (float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
	return *this;
}

float Vector3::Dot (const Vector3 &op2) const
{
	return DotProduct (*this,op2);
}

Vector3 Vector3::Cross (const Vector3 &op2) const
{
	return CrossProduct (*this,op2);
}

Vector3 &Vector3::Normalize ()
{
	float len = Length ();
	X /= len;
	Y /= len;
	Z /= len;
	return *this;
}

float Vector3::Length () const
{
	return sqrt (X * X + Y * Y + Z * Z);
}

float Vector3::LengthSquared () const
{
	return X * X + Y * Y + Z * Z;
}

float Vector3::Distance (const Vector3 &op2) const
{
	return (op2 - *this).Length ();
}

float Vector3::DistanceSquared (const Vector3 &op2) const
{
	return (op2 - *this).LengthSquared ();
}

bool Vector3::WithinDistance (const Vector3 &point, float dist) const
{
	return DistanceSquared (point) < dist * dist;
}

float Vector3::DotProduct (const Vector3 &op1, const Vector3 &op2)
{
	return op1.X * op2.X + op1.Y * op2.Y + op1.Z * op2.Z;
}

Vector3 Vector3::CrossProduct (const Vector3 &op1, const Vector3 &op2)
{
	Vector3 result;
	result.X =  (op1.Y * op2.Z) - (op2.Y * op1.Z);
	result.Y = -((op1.X * op2.Z) - (op2.X * op1.Z));
	result.Z =  (op1.X * op2.Y) - (op2.X * op1.Y);
	return result;
}

bool Vector3::operator== (const Vector3 &op2) const
{
	return op2.X == X && op2.Y == Y && op2.Z == Z;
}
bool Vector3::operator!= (const Vector3 &op2) const
{
	return op2.X != X || op2.Y != Y || op2.Z != Z;
}

Vector3 &Vector3::operator+= (const Vector3 &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	return *this;
}
Vector3 &Vector3::operator-= (const Vector3 &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	return *this;
}
Vector3 &Vector3::operator*= (float op2)
{
	X *= op2;
	Y *= op2;
	Z *= op2;
	return *this;
}

Vector3 operator- (const Vector3 &op1, const Vector3 &op2)
{
	return Vector3 (op1.X - op2.X, op1.Y - op2.Y, op1.Z - op2.Z);
}
Vector3 operator+ (const Vector3 &op1, const Vector3 &op2)
{
	return Vector3 (op1.X + op2.X, op1.Y + op2.Y, op1.Z + op2.Z);
}
Vector3 operator* (const Vector3 &op1, float op2)
{
    return Vector3 (op1.X * op2, op1.Y * op2, op1.Z * op2);
}
Vector3 operator* (float op1, const Vector3 &op2)
{
	return Vector3 (op2.X * op1, op2.Y * op1, op2.Z * op1);
}
Vector3 operator/ (const Vector3 &op1, float op2)
{
	return Vector3 (op1.X / op2, op1.Y / op2, op1.Z / op2);
}

}}