#include "Vector4.h"
#include "Util.h"
#include <cmath>

namespace Tocs {
namespace Math {

Vector4 &Vector4::Normalize ()
{
	float len = Length();
	X /= len;
	Y /= len;
	Z /= len;
	W /= len;
	return *this;
}

float Vector4::Dot (const Vector4 &op2) const
{
	return X * op2.X + Y * op2.Y + Z * op2.Z + W * op2.W;
}

float Vector4::Length () const
{
	return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

float Vector4::LengthSquared () const
{
	return X * X + Y * Y + Z * Z + W * W;
}

float Vector4::Distance (const Vector4 &op2) const
{
	return (op2 - *this).Length ();
}

float Vector4::DistanceSquared (const Vector4 &op2) const
{
	return (op2 - *this).LengthSquared ();
}

bool Vector4::WithinDistance (const Vector4 &point, float distance) const
{
	return DistanceSquared (point) < distance * distance;
}

float Vector4::DotProduct (const Vector4 &op1, const Vector4 &op2)
{
	return op1.X * op2.X + op1.Y * op2.Y + op1.Z * op2.Z + op1.W * op2.W;
}

Vector4 Vector4::Normalized (const Vector4 &vector)
{
	return vector / vector.Length();
}

bool Vector4::operator== (const Vector4 &op2) const
{
	return op2.X == X && op2.Y == Y && op2.Z == Z && op2.W == W;
}

bool Vector4::operator!= (const Vector4 &op2) const
{
	return op2.X != X || op2.Y != Y || op2.Z != Z || op2.W != W;
}

Vector4 &Vector4::operator+= (const Vector4 &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	W += op2.W;
	return *this;
}

Vector4 &Vector4::operator-= (const Vector4 &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	W -= op2.W;
	return *this;
}

Vector4 &Vector4::operator*= (float op2)
{
	X *= op2;
	Y *= op2;
	Z *= op2;
	W *= op2;
	return *this;
}

Vector4 &Vector4::operator/= (float op2)
{
	X /= op2;
	Y /= op2;
	Z /= op2;
	W /= op2;
	return *this;
}

Vector4 operator- (const Vector4 &op1, const Vector4 &op2)
{
	return Vector4 (op1.X - op2.X, op1.Y - op2.Y, op1.Z - op2.Z, op1.W - op2.W);
}
Vector4 operator+ (const Vector4 &op1, const Vector4 &op2)
{
	return Vector4 (op1.X + op2.X, op1.Y + op2.Y, op1.Z + op2.Z, op1.W + op2.W);
}
Vector4 operator* (const Vector4 &op1, float op2)
{
	return Vector4 (op1.X * op2, op1.Y * op2, op1.Z * op2, op1.W * op2);
}
Vector4 operator* (float op1, const Vector4 &op2)
{
	return Vector4 (op2.X * op1, op2.Y * op1, op2.Z * op1, op2.W * op1);
}
Vector4 operator/ (const Vector4 &op1, float op2)
{
	return Vector4 (op1.X / op2, op1.Y / op2, op1.Z / op2, op1.W / op2);
}
std::ostream &operator<< (std::ostream &stream, const Vector4 &vec)
{
	stream << "<" << vec.X << ", " << vec.Y << ", " << vec.Z << ", " << vec.W << ">";
	return stream;
}

Vector4 Clamp (Vector4 value, Vector4 min, Vector4 max)
{
	return Vector4 (Clamp (value.X,min.X,max.X),Clamp (value.Y,min.Y,max.Y),Clamp (value.Z,min.Z,max.Z),Clamp (value.W,min.W,max.W));
}

}}