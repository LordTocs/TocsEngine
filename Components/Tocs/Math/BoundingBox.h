#pragma once

#include "Vector.h"
#include "Matrix4.h"

#include <limits>

namespace Tocs {
namespace Math {

template <class Kernel>
class BoundingBoxBase
{
	VectorBase<Kernel,3> Center_;
	VectorBase<Kernel,3> Reach_;

	static void FixMinMax(VectorBase<Kernel, 3> &min, VectorBase<Kernel, 3> &max)
	{
		if (min.X > max.X)
		{
			std::swap(min.X, max.X);
		}
		if (min.Y > max.Y)
		{
			std::swap(min.Y, max.Y);
		}
		if (min.Z > max.Z)
		{
			std::swap(min.Z, max.Z);
		}
	}

public:
	BoundingBoxBase(const VectorBase<Kernel, 3> &center, const VectorBase<Kernel, 3> &reach)
		: Center_(center), Reach_(reach) {}

	BoundingBoxBase () {}


	static BoundingBoxBase MinMax(VectorBase<Kernel, 3> min, VectorBase<Kernel, 3> max)
	{
		FixMinMax(min, max);
		return BoundingBoxBase((min + max) / Kernel(2), (max - min) / Kernel(2));
	}

	const VectorBase<Kernel, 3> &Center() const { return Center_; }
	BoundingBoxBase &Center (const VectorBase<Kernel,3> &center) { Center_ = center; return *this; }
	BoundingBoxBase &Center (Kernel x, Kernel y, Kernel z) { Center_(x,y,z); return *this; }

	const VectorBase<Kernel,3> &Reach () const { return _Reach; }
	BoundingBoxBase &Reach(const VectorBase<Kernel, 3> &reach)
	{
		Reach_(std::abs(reach.X), std::abs(reach.Y), std::abs(reach.Z));
		return *this;
	}
	BoundingBoxBase &Reach(Kernel wr, Kernel lr, Kernel hr)
	{
		Reach_(std::abs(wr), std::abs(lr), std::abs(hr));
		return *this;
	}

	Kernel Width () const  { return 2*Reach_.X; }
	Kernel Height () const { return 2*Reach_.Y; }
	Kernel Length () const { return 2*Reach_.Z; }

	VectorBase<Kernel,3> Min () const { return Center_ - Reach_; }
	VectorBase<Kernel,3> Max () const { return Center_ + Reach_; }

	BoundingBoxBase &Min(const VectorBase<Kernel, 3> &min)
	{
		(*this) = MinMax(min, Max());
		return *this;
	}
	BoundingBoxBase &Max(const VectorBase<Kernel, 3> &max)
	{
		(*this) = MinMax(Min(), max);
		return *this;
	}
	BoundingBoxBase &Min(Kernel x, Kernel y, Kernel z)
	{
		(*this) = MinMax(VectorBase<Kernel, 3>(x, y, z), Max());
		return *this;
	}
	BoundingBoxBase &Max(Kernel x, Kernel y, Kernel z)
	{
		(*this) = MinMax(Min(), VectorBase<Kernel, 3>(x, y, z));
		return *this;
	}

	VectorBase<Kernel, 3> operator[](unsigned int i) const
	{
		VectorBase<Kernel, 3> offset;
		if (i >= 4)
		{
			offset.Y = -Reach_.Y;
		}
		else
		{
			offset.Y = Reach_.Y;
		}

		i %= 4;

		if (i >= 2)
		{
			offset.Z = -Reach_.Z;
		}
		else
		{
			offset.Z = Reach_.Z;
		}

		i %= 2;

		if (i >= 1)
		{
			offset.X = Reach_.X;
		}
		else
		{
			offset.X = -Reach_.X;
		}

		return Center_ + offset;
	}
};

typedef BoundingBoxBase<float> BoundingBox;
typedef BoundingBoxBase<int> BoundingBoxi;
typedef BoundingBoxBase<unsigned int> BoundingBoxui;

BoundingBox EncapsulateTransformedBoundingBox(const BoundingBox &box, const Matrix4 &transform);

template <class Kernel>
class BoundingBox2DBase
{
	VectorBase<Kernel,2> Center_;
	VectorBase<Kernel,2> Reach_;

	static void FixMinMax(VectorBase<Kernel, 2> &min, VectorBase<Kernel, 2> &max)
	{
		if (min.X > max.X)
		{
			std::swap(min.X, max.X);
		}
		if (min.Y > max.Y)
		{
			std::swap(min.Y, max.Y);
		}
	}

public:
	BoundingBox2DBase(const VectorBase<Kernel,2> &center, const VectorBase<Kernel,2> &reach)
		: Center_(center), Reach_(reach) {}

	BoundingBox2DBase () {}

	static BoundingBox2DBase MinMax(VectorBase<Kernel, 2> min, VectorBase<Kernel, 2> max)
	{
		FixMinMax(min,max);
		return BoundingBox2DBase((min + max) / Kernel(2), (max - min) / Kernel(2));
	}

	const VectorBase<Kernel,2> &Center () const { return Center_; }
	BoundingBox2DBase &Center(const VectorBase<Kernel, 2> &center) { Center_ = center; return *this; }
	BoundingBox2DBase &Center(Kernel x, Kernel y) { Center_(x, y); return *this; }

	const VectorBase<Kernel,2> &Reach () const { return Reach_; }
	BoundingBox2DBase &Reach(const VectorBase<Kernel, 2> &reach)
	{
		Reach_(std::abs(reach.X), std::abs(reach.Y));
		return *this;
	}
	BoundingBox2DBase &Reach(Kernel wr, Kernel lr)
	{
		Reach_(std::abs(wr), std::abs(hr));
		return *this;
	}

	Kernel Width () const { return Kernel(2)*Reach_.X; }
	Kernel Height () const { return Kernel(2)*Reach_.Y; }

	BoundingBox2DBase &Width(Kernel w) { Reach_.X = w / Kernel(2); return *this; }
	BoundingBox2DBase &Height(Kernel h) { Reach_.Y = h / Kernel(2); return *this; }

	VectorBase<Kernel,2> Min () const { return Center_ - Reach_; }
	VectorBase<Kernel,2> Max () const { return Center_ + Reach_; }

	BoundingBox2DBase &Min(const VectorBase<Kernel, 2> &min)
	{
		(*this) = MinMax(min, Max());
		return *this;
	}
	BoundingBox2DBase &Max(const VectorBase<Kernel, 2> &min)
	{
		(*this) = MinMax(Min(), max);
		return *this;
	}
	BoundingBox2DBase &Min(Kernel x, Kernel y)
	{
		(*this) = MinMax(Vector2(x, y), Max());
		return *this;
	}
	BoundingBox2DBase &Max(Kernel x, Kernel y)
	{
		(*this) = MinMax(Min(), Vector2(x, y));
		return *this;
	}

	void Encapsulate(const Math::VectorBase<Kernel, 2> &point)
	{
		VectorBase<Kernel, 2> min = Min();
		VectorBase<Kernel, 2> max = Max();

		if (point.X < min.X)
			min.X = point.X;
		if (point.X > max.X)
			max.X = point.X;

		if (point.Y < min.Y)
			min.Y = point.Y;
		if (point.Y > max.Y)
			max.Y = point.Y;

		(*this) = MinMax(min, max);
	}
};

typedef BoundingBox2DBase<float> BoundingBox2D;
typedef BoundingBox2DBase<int> BoundingBox2Di;
typedef BoundingBox2DBase<unsigned int> BoundingBox2Dui;

}}

