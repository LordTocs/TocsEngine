#include "Vector4i.h"
#include <cmath>

namespace Tocs {
namespace Math {


int Vector4i::Dot (const Vector4i &op2) const
{
	return X * op2.X + Y * op2.Y + Z * op2.Z + W * op2.W;
}

float Vector4i::Length () const
{
	return std::sqrt((float)X * X + Y * Y + Z * Z + W * W);
}

float Vector4i::LengthSquared () const
{
	return X * X + Y * Y + Z * Z + W * W;
}

float Vector4i::Distance (const Vector4i &op2) const
{
	return (op2 - *this).Length ();
}

float Vector4i::DistanceSquared (const Vector4i &op2) const
{
	return (op2 - *this).LengthSquared ();
}

bool Vector4i::WithinDistance (const Vector4i &point, int distance) const
{
	return DistanceSquared (point) < distance * distance;
}

int Vector4i::DotProduct (const Vector4i &op1, const Vector4i &op2)
{
	return op1.X * op2.X + op1.Y * op2.Y + op1.Z * op2.Z + op1.W * op2.W;
}

bool Vector4i::operator== (const Vector4i &op2) const
{
	return op2.X == X && op2.Y == Y && op2.Z == Z && op2.W == W;
}

bool Vector4i::operator!= (const Vector4i &op2) const
{
	return op2.X != X || op2.Y != Y || op2.Z != Z || op2.W != W;
}

Vector4i &Vector4i::operator+= (const Vector4i &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	W += op2.W;
	return *this;
}

Vector4i &Vector4i::operator-= (const Vector4i &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	W -= op2.W;
	return *this;
}

Vector4i &Vector4i::operator*= (int op2)
{
	X *= op2;
	Y *= op2;
	Z *= op2;
	W *= op2;
	return *this;
}

Vector4i &Vector4i::operator/= (int op2)
{
	X /= op2;
	Y /= op2;
	Z /= op2;
	W /= op2;
	return *this;
}

Vector4i operator- (const Vector4i &op1, const Vector4i &op2)
{
	return Vector4i (op1.X - op2.X, op1.Y - op2.Y, op1.Z - op2.Z, op1.W - op2.W);
}
Vector4i operator+ (const Vector4i &op1, const Vector4i &op2)
{
	return Vector4i (op1.X + op2.X, op1.Y + op2.Y, op1.Z + op2.Z, op1.W + op2.W);
}
Vector4i operator* (const Vector4i &op1, int op2)
{
	return Vector4i (op1.X * op2, op1.Y * op2, op1.Z * op2, op1.W * op2);
}
Vector4i operator* (int op1, const Vector4i &op2)
{
	return Vector4i (op2.X * op1, op2.Y * op1, op2.Z * op1, op2.W * op1);
}
Vector4i operator/ (const Vector4i &op1, int op2)
{
	return Vector4i (op1.X / op2, op1.Y / op2, op1.Z / op2, op1.W / op2);
}
std::ostream &operator<< (std::ostream &stream, const Vector4i &vec)
{
	stream << "<" << vec.X << ", " << vec.Y << ", " << vec.Z << ", " << vec.W << ">";
	return stream;
}

}}