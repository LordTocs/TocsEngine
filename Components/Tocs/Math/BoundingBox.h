#pragma once

#include "Vector.h"

#include <limits>

namespace Tocs {
namespace Math {

class BoundingBox
{
	Vector3 _Center;
	Vector3 _Reach;
public:
	BoundingBox(const Vector3 &center, const Vector3 &reach)
		: _Center(center), _Reach(reach) {}

	BoundingBox () {}

	static BoundingBox MinMax (Vector3 min, Vector3 max);

	const Vector3 &Center () const { return _Center; }
	BoundingBox &Center (const Vector3 &center) { _Center = center; return *this; }
	BoundingBox &Center (float x, float y, float z) { _Center(x,y,z); return *this; }

	const Vector3 &Reach () const { return _Reach; }
	BoundingBox &Reach(const Vector3 &reach);
	BoundingBox &Reach(float wr, float lr, float hr);

	float Width () const  { return 2*_Reach.X; }
	float Height () const { return 2*_Reach.Y; }
	float Length () const { return 2*_Reach.Z; }

	Vector3 Min () const { return _Center - _Reach; }
	Vector3 Max () const { return _Center + _Reach; }

	BoundingBox &Min (const Vector3 &min);
	BoundingBox &Max (const Vector3 &min);
	BoundingBox &Min (float x, float y, float z);
	BoundingBox &Max (float x, float y, float z);

	Vector3 Corner (int index) const;

	bool CompletelyContains (const BoundingBox &box) const;

	template<class T>
	static BoundingBox Fit (T *points, int pointcount)
	{
		Vector3 min(std::numeric_limits<float>::max(),std::numeric_limits<float>::max(),std::numeric_limits<float>::max());
		Vector3 max(std::numeric_limits<float>::min(),std::numeric_limits<float>::min(),std::numeric_limits<float>::min());
		
		for (int i = 0; i < pointcount; ++i)
		{
			min.X = (min.X > points[i].Position.X ? points[i].Position.X : min.X);
			min.Y = (min.Y > points[i].Position.Y ? points[i].Position.Y : min.Y);
			min.Z = (min.Z > points[i].Position.Z ? points[i].Position.Z : min.Z);

			max.X = (max.X < points[i].Position.X ? points[i].Position.X : max.X);
			max.Y = (max.Y < points[i].Position.Y ? points[i].Position.Y : max.Y);
			max.Z = (max.Z < points[i].Position.Z ? points[i].Position.Z : max.Z);
		}

		return MinMax(min,max);
	}
};

class BoundingBox2D
{
	Vector2 _Center;
	Vector2 _Reach;
public:
	BoundingBox2D(const Vector2 &center, const Vector2 &reach)
		: _Center(center), _Reach(reach) {}

	BoundingBox2D () {}

	static BoundingBox2D MinMax (Vector2 min, Vector2 max);

	const Vector2 &Center () const { return _Center; }
	BoundingBox2D &Center (const Vector2 &center) { _Center = center; return *this; }
	BoundingBox2D &Center (float x, float y) { _Center(x,y); return *this; }

	const Vector2 &Reach () const { return _Reach; }
	BoundingBox2D &Reach(const Vector2 &reach);
	BoundingBox2D &Reach(float wr, float lr);

	float Width () const { return 2*_Reach.X; }
	float Heighth () const { return 2*_Reach.Y; }

	Vector2 Min () const { return _Center - _Reach; }
	Vector2 Max () const { return _Center + _Reach; }

	BoundingBox2D &Min (const Vector2 &min);
	BoundingBox2D &Max (const Vector2 &min);
	BoundingBox2D &Min (float x, float y);
	BoundingBox2D &Max (float x, float y);

	void Encapsulate (const Math::Vector2 &point);

	template<class T>
	static BoundingBox2D Fit (T *points, int pointcount)
	{
		Vector2 min(std::numeric_limits<float>::max(),std::numeric_limits<float>::max());
		Vector2 max(std::numeric_limits<float>::min(),std::numeric_limits<float>::min());
		
		for (int i = 0; i < pointcount; ++i)
		{
			min.X = (min.X > points[i].Position.X ? points[i].Position.X : min.X);
			min.Y = (min.Y > points[i].Position.Y ? points[i].Position.Y : min.Y);

			max.X = (max.X < points[i].Position.X ? points[i].Position.X : max.X);
			max.Y = (max.Y < points[i].Position.Y ? points[i].Position.Y : max.Y);
		}

		return MinMax(min,max);
	}
};


}}

