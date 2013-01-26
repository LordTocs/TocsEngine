#include "Vector2.h"
#include <math.h>

namespace Tocs {
namespace Math {

Vector2::Vector2()
	: X (0),
	  Y (0)
{}

Vector2::Vector2 (float x, float y)
	: X (x),
	  Y (y)
{}

Vector2 &Vector2::operator () (float x, float y)
{
	X = x;
	Y = y;
	return *this;
}

float Vector2::Dot (const Vector2 &op2) const
{
	return DotProduct (*this,op2);
}

/*Vector2 Vector2::Cross (const Vector2 &op2) const
{
	return CrossProduct (*this,op2);
}*/

Vector2 &Vector2::Normalize ()
{
	float len = Length ();
	X /= len;
	Y /= len;
	return *this;
}

float Vector2::Length () const
{
	return sqrt (X * X + Y * Y);
}

float Vector2::LengthSquared () const
{
	return X * X + Y * Y;
}

float Vector2::Distance (const Vector2 &op2) const
{
	return (op2 - *this).Length ();
}

float Vector2::DistanceSquared (const Vector2 &op2) const
{
	return (op2 - *this).LengthSquared ();
}

bool Vector2::WithinDistance (const Vector2 &point, float dist) const
{
	return DistanceSquared (point) < dist * dist;
}

float Vector2::DotProduct (const Vector2 &op1, const Vector2 &op2)
{
	return op1.X * op2.X + op1.Y * op2.Y;
}

/*Vector2 Vector2::CrossProduct (const Vector2 &op1, const Vector2 &op2)
{
	Vector2 result;
	result.X =  (op1.Y * op2.Z) - (op2.Y * op1.Z);
	result.Y = -((op1.X * op2.Z) - (op2.X * op1.Z));
	result.Z =  (op1.X * op2.Y) - (op2.X * op1.Y);
	return result;
}*/

bool Vector2::operator== (const Vector2 &op2) const
{
	return op2.X == X && op2.Y == Y;
}
bool Vector2::operator!= (const Vector2 &op2) const
{
	return op2.X != X || op2.Y != Y;
}

Vector2 &Vector2::operator+= (const Vector2 &op2)
{
	X += op2.X;
	Y += op2.Y;
	return *this;
}
Vector2 &Vector2::operator-= (const Vector2 &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	return *this;
}
Vector2 &Vector2::operator*= (float op2)
{
	X *= op2;
	Y *= op2;
	return *this;
}

Vector2 operator- (const Vector2 &op1, const Vector2 &op2)
{
	return Vector2 (op1.X - op2.X, op1.Y - op2.Y);
}
Vector2 operator+ (const Vector2 &op1, const Vector2 &op2)
{
	return Vector2 (op1.X + op2.X, op1.Y + op2.Y);
}
Vector2 operator* (const Vector2 &op1, float op2)
{
    return Vector2 (op1.X * op2, op1.Y * op2);
}
Vector2 operator* (float op1, const Vector2 &op2)
{
	return Vector2 (op2.X * op1, op2.Y * op1);
}
Vector2 operator/ (const Vector2 &op1, float op2)
{
	return Vector2 (op1.X / op2, op1.Y / op2);
}

}}