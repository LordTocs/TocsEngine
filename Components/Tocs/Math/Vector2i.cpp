#include "Vector2i.h"
#include <cmath>

namespace Tocs {
namespace Math {

Vector2i::Vector2i()
	: X (0),
	  Y (0)
{}

Vector2i::Vector2i (int x, int y)
	: X (x),
	  Y (y)
{}

Vector2i &Vector2i::operator () (int x, int y)
{
	X = x;
	Y = y;
	return *this;
}

int Vector2i::Dot (const Vector2i &op2) const
{
	return DotProduct (*this,op2);
}

float Vector2i::Length () const
{
	return std::sqrt (static_cast<float>(X * X + Y * Y));
}

float Vector2i::LengthSquared () const
{
	return X * X + Y * Y;
}

float Vector2i::Distance (const Vector2i &op2) const
{
	return (op2 - *this).Length ();
}

float Vector2i::DistanceSquared (const Vector2i &op2) const
{
	return (op2 - *this).LengthSquared ();
}

bool Vector2i::WithinDistance (const Vector2i &point, float dist) const
{
	return DistanceSquared (point) < dist * dist;
}

int Vector2i::DotProduct (const Vector2i &op1, const Vector2i &op2)
{
	return op1.X * op2.X + op1.Y * op2.Y;
}


bool Vector2i::operator== (const Vector2i &op2) const
{
	return op2.X == X && op2.Y == Y;
}
bool Vector2i::operator!= (const Vector2i &op2) const
{
	return op2.X != X || op2.Y != Y;
}

Vector2i &Vector2i::operator+= (const Vector2i &op2)
{
	X += op2.X;
	Y += op2.Y;
	return *this;
}
Vector2i &Vector2i::operator-= (const Vector2i &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	return *this;
}
Vector2i &Vector2i::operator*= (int op2)
{
	X *= op2;
	Y *= op2;
	return *this;
}

Vector2i operator- (const Vector2i &op1, const Vector2i &op2)
{
	return Vector2i (op1.X - op2.X, op1.Y - op2.Y);
}
Vector2i operator+ (const Vector2i &op1, const Vector2i &op2)
{
	return Vector2i (op1.X + op2.X, op1.Y + op2.Y);
}
Vector2i operator* (const Vector2i &op1, int op2)
{
    return Vector2i (op1.X * op2, op1.Y * op2);
}
Vector2i operator* (int op1, const Vector2i &op2)
{
	return Vector2i (op2.X * op1, op2.Y * op1);
}
Vector2i operator/ (const Vector2i &op1, int op2)
{
	return Vector2i (op1.X / op2, op1.Y / op2);
}

}}