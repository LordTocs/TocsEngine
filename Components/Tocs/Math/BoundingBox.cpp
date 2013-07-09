#include "BoundingBox.h"

namespace Tocs {
namespace Math {

static void FixMinMax (Vector3 &min, Vector3 &max)
{
	if (min.X > max.X)
	{
		std::swap(min.X,max.X);
	}
	if (min.Y > max.Y)
	{
		std::swap(min.Y,max.Y);
	}
	if (min.Z > max.Z)
	{
		std::swap(min.Z,max.Z);
	}
}

BoundingBox BoundingBox::MinMax (Vector3 min, Vector3 max)
{
	FixMinMax(min,max);
	Vector3 center = (min + max) /2;
	Vector3 reach = (max - min) /2;

	BoundingBox box;
	box._Center = center;
	box._Reach = reach;
	return box;
}


BoundingBox &BoundingBox::Reach(const Vector3 &reach)
{
	_Reach(std::abs(reach.X),std::abs(reach.Y),std::abs(reach.Z));
	return *this;
}

BoundingBox &BoundingBox::Reach(float wr, float hr, float lr)
{
	_Reach(std::abs(wr),std::abs(hr),std::abs(lr));
	return *this;
}

BoundingBox &BoundingBox::Min (const Vector3 &min)
{
	(*this) = MinMax (min,Max());
	return *this;
}

BoundingBox &BoundingBox::Max (const Vector3 &max)
{
	(*this) = MinMax (Min(),max);
	return *this;
}

BoundingBox &BoundingBox::Min (float x, float y, float z)
{
	(*this) = MinMax (Vector3(x,y,z),Max());
	return *this;
}

BoundingBox &BoundingBox::Max (float x, float y, float z)
{
	(*this) = MinMax (Min(),Vector3(x,y,z));
	return *this;
}

//////////////////////////

static void FixMinMax (Vector2 &min, Vector2 &max)
{
	if (min.X > max.X)
	{
		std::swap(min.X,max.X);
	}
	if (min.Y > max.Y)
	{
		std::swap(min.Y,max.Y);
	}
}

BoundingBox2D BoundingBox2D::MinMax (Vector2 min, Vector2 max)
{
	FixMinMax(min,max);
	Vector2 center = (min + max) /2;
	Vector2 reach = (max - min) /2;

	BoundingBox2D box;
	box._Center = center;
	box._Reach = reach;
	return box;
}


BoundingBox2D &BoundingBox2D::Reach(const Vector2 &reach)
{
	_Reach(std::abs(reach.X),std::abs(reach.Y));
	return *this;
}

BoundingBox2D &BoundingBox2D::Reach(float wr, float hr)
{
	_Reach(std::abs(wr),std::abs(hr));
	return *this;
}

BoundingBox2D &BoundingBox2D::Min (const Vector2 &min)
{
	(*this) = MinMax (min,Max());
	return *this;
}

BoundingBox2D &BoundingBox2D::Max (const Vector2 &max)
{
	(*this) = MinMax (Min(),max);
	return *this;
}

BoundingBox2D &BoundingBox2D::Min (float x, float y)
{
	(*this) = MinMax (Vector2(x,y),Max());
	return *this;
}

BoundingBox2D &BoundingBox2D::Max (float x, float y)
{
	(*this) = MinMax (Min(),Vector2(x,y));
	return *this;
}

void BoundingBox2D::Encapsulate (const Math::Vector2 &point)
{
	Math::Vector2 min = Min();
	Math::Vector2 max = Max();

	if (point.X < min.X)
		min.X = point.X;
	if (point.X > max.X)
		max.X = point.X;

	if (point.Y < min.Y)
		min.Y = point.Y;
	if (point.Y > max.Y)
		max.Y = point.Y;

	(*this) = MinMax (min,max);
}


}}