#include "Vector3i.h"

namespace Tocs {
namespace Math {

Vector3i::Vector3i()
	: X (0),
	  Y (0),
	  Z (0)
{}

Vector3i::Vector3i (int x, int y, int z)
	: X (x),
	  Y (y),
	  Z (z)
{}

Vector3i &Vector3i::operator () (int x, int y, int z)
{
	X = x;
	Y = y;
	Z = z;
	return *this;
}

int Vector3i::Dot (const Vector3i &op2) const
{
	return DotProduct (*this,op2);
}

Vector3i Vector3i::Cross (const Vector3i &op2) const
{
	return CrossProduct (*this,op2);
}


float Vector3i::Length () const
{
	return std::sqrt ((float)(X * X + Y * Y + Z * Z));
}

float Vector3i::LengthSquared () const
{
	return X * X + Y * Y + Z * Z;
}

float Vector3i::Distance (const Vector3i &op2) const
{
	return (op2 - *this).Length ();
}

float Vector3i::DistanceSquared (const Vector3i &op2) const
{
	return (op2 - *this).LengthSquared ();
}

bool Vector3i::WithinDistance (const Vector3i &point, float dist) const
{
	return DistanceSquared (point) < dist * dist;
}

int Vector3i::DotProduct (const Vector3i &op1, const Vector3i &op2)
{
	return op1.X * op2.X + op1.Y * op2.Y + op1.Z * op2.Z;
}

Vector3i Vector3i::CrossProduct (const Vector3i &op1, const Vector3i &op2)
{
	Vector3i result;
	result.X =  (op1.Y * op2.Z) - (op2.Y * op1.Z);
	result.Y = -((op1.X * op2.Z) - (op2.X * op1.Z));
	result.Z =  (op1.X * op2.Y) - (op2.X * op1.Y);
	return result;
}

bool Vector3i::operator== (const Vector3i &op2) const
{
	return op2.X == X && op2.Y == Y && op2.Z == Z;
}
bool Vector3i::operator!= (const Vector3i &op2) const
{
	return op2.X != X || op2.Y != Y || op2.Z != Z;
}

Vector3i &Vector3i::operator+= (const Vector3i &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	return *this;
}
Vector3i &Vector3i::operator-= (const Vector3i &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	return *this;
}
Vector3i &Vector3i::operator*= (float op2)
{
	X *= op2;
	Y *= op2;
	Z *= op2;
	return *this;
}

Vector3i operator- (const Vector3i &op1, const Vector3i &op2)
{
	return Vector3i (op1.X - op2.X, op1.Y - op2.Y, op1.Z - op2.Z);
}
Vector3i operator+ (const Vector3i &op1, const Vector3i &op2)
{
	return Vector3i (op1.X + op2.X, op1.Y + op2.Y, op1.Z + op2.Z);
}
Vector3i operator* (const Vector3i &op1, int op2)
{
    return Vector3i (op1.X * op2, op1.Y * op2, op1.Z * op2);
}
Vector3i operator* (int op1, const Vector3i &op2)
{
	return Vector3i (op2.X * op1, op2.Y * op1, op2.Z * op1);
}
Vector3i operator/ (const Vector3i &op1, int op2)
{
	return Vector3i (op1.X / op2, op1.Y / op2, op1.Z / op2);
}

std::ostream &operator<< (std::ostream &stream, const Vector3i &vec)
{
	stream << "<" << vec.X << ", " << vec.Y << ", " << vec.Z << ">";
	return stream;
}

}}