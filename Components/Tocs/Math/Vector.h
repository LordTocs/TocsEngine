#pragma once
#include <type_traits>
#include <cmath>
#include <Tocs/Core/MemberChecks.h>
#include "Util.h"
namespace Tocs {
namespace Math {

template <class Kernel>
class FloatingPointKernel;

template <>
class FloatingPointKernel<int>
{
public:
	typedef float Type;
};
template <>
class FloatingPointKernel<unsigned int>
{
public:
	typedef float Type;
};
template <>
class FloatingPointKernel<short>
{
public:
	typedef float Type;
};
template <>
class FloatingPointKernel<unsigned short>
{
public:
	typedef float Type;
};
template <>
class FloatingPointKernel<float>
{
public:
	typedef float Type;
};
template <>
class FloatingPointKernel<double>
{
public:
	typedef double Type;
};


template <class Kernel, unsigned int Components>
class VectorBase
{
	Kernel Data[Components];
public:
	VectorBase ()
		: Data () {}

	Kernel &operator[] (unsigned int i)
	{ return Data[i]; }

	const Kernel &operator[] (unsigned int i) const
	{ return Data[i]; }

	Kernel Dot(const VectorBase &op2) const;

	typename FloatingPointKernel<Kernel>::Type Length () const;
	typename FloatingPointKernel<Kernel>::Type LengthSquared () const;
	typename FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	typename FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, typename FloatingPointKernel<Kernel>::Type distance) const;

	VectorBase Normalized () const;
	VectorBase &Normalize ();

	bool operator== (const VectorBase &op2) const;
	bool operator!= (const VectorBase &op2) const;

	VectorBase &operator+= (const VectorBase &op2);
	VectorBase &operator-= (const VectorBase &op2);
	VectorBase &operator*= (Kernel op2);
	VectorBase &operator/= (Kernel op2);


};

template <class Kernel>
class VectorBase <Kernel,2>
{
public:
	Kernel X,Y;

	VectorBase ()
		: X(), Y() {}

	VectorBase (Kernel x, Kernel y)
		: X(x), Y(y) {}

	VectorBase &operator()(Kernel x, Kernel y)
	{	X = x; Y = y; return *this; }

	Kernel &operator[] (unsigned int i)
	{ return *(&X + i); }

	const Kernel &operator[] (unsigned int i) const
	{ return *(&X + i); }

	Kernel Dot(const VectorBase &op2) const; //{ return VectorBase(X * op2.X, Y * op2.Y, Z * op2.Z); }

	Kernel Cross(const VectorBase &op2) const
	{
		return (X * op2.Y) - (X * op1.Y);
	}

	typename FloatingPointKernel<Kernel>::Type Length () const;
	typename FloatingPointKernel<Kernel>::Type LengthSquared () const;
	typename FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	typename FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, typename FloatingPointKernel<Kernel>::Type distance) const;

	VectorBase Normalized () const;
	VectorBase &Normalize ();

	bool operator== (const VectorBase &op2) const;
	bool operator!= (const VectorBase &op2) const;

	VectorBase &operator+= (const VectorBase &op2);
	VectorBase &operator-= (const VectorBase &op2);
	VectorBase &operator*= (Kernel op2);
	VectorBase &operator/= (Kernel op2);
};

template <class Kernel>
class VectorBase <Kernel,3>
{
public:
	Kernel X,Y,Z;

	VectorBase ()
		: X(), Y(), Z() {}

	VectorBase (Kernel x, Kernel y, Kernel z)
		: X(x), Y(y), Z(z) {}

	VectorBase &operator()(Kernel x, Kernel y, Kernel z)
	{	X = x; Y = y; Z = z; return *this;	}

	Kernel &operator[] (unsigned int i)
	{ return *(&X + i); }

	const Kernel &operator[] (unsigned int i) const
	{ return *(&X + i); }

	Kernel Dot (const VectorBase &op2) const; //{ return VectorBase(X * op2.X, Y * op2.Y, Z * op2.Z); }

	VectorBase Cross (const VectorBase &op2) const
	{
		VectorBase<Kernel,3> result;
		result.X =  (Y * op2.Z) - (op2.Y * Z);
		result.Y = -((X * op2.Z) - (op2.X * Z));
		result.Z =  (X * op2.Y) - (op2.X * Y);
		return result;
	}

	typename FloatingPointKernel<Kernel>::Type Length () const;
	typename FloatingPointKernel<Kernel>::Type LengthSquared () const;
	typename FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	typename FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, typename FloatingPointKernel<Kernel>::Type distance) const;

	VectorBase Normalized () const;
	VectorBase &Normalize ();

	bool operator== (const VectorBase &op2) const;
	bool operator!= (const VectorBase &op2) const;

	VectorBase &operator+= (const VectorBase &op2);
	VectorBase &operator-= (const VectorBase &op2);
	VectorBase &operator*= (Kernel op2);
	VectorBase &operator/= (Kernel op2);
};

template <class Kernel>
class VectorBase <Kernel,4>
{
public:
	Kernel X,Y,Z,W;

	VectorBase ()
		: X(), Y(), Z(), W() {}

	VectorBase (Kernel x, Kernel y, Kernel z, Kernel w)
		: X(x), Y(y), Z(z), W(w) {}

	VectorBase &operator()(Kernel x, Kernel y, Kernel z, Kernel w)
	{	X = x; Y = y; Z = z; W = w; return *this;	}

	Kernel &operator[] (unsigned int i)
	{ return *(&X + i); }

	const Kernel &operator[] (unsigned int i) const
	{ return *(&X + i); }

	Kernel Dot (const VectorBase &op2) const; //{ return VectorBase(X * op2.X, Y * op2.Y, Z * op2.Z); }

	VectorBase Cross (const VectorBase &op2)
	{
		VectorBase result;
		result.X =  (Y * op2.Z) - (Y * op1.Z);
		result.Y = -((X * op2.Z) - (X * op1.Z));
		result.Z =  (X * op2.Y) - (X * op1.Y);
		return result;
	}

	typename FloatingPointKernel<Kernel>::Type Length () const;
	typename FloatingPointKernel<Kernel>::Type LengthSquared () const;
	typename FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	typename FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, typename FloatingPointKernel<Kernel>::Type distance) const;

	VectorBase Normalized () const;
	VectorBase &Normalize ();

	bool operator== (const VectorBase &op2) const;
	bool operator!= (const VectorBase &op2) const;

	VectorBase &operator+= (const VectorBase &op2);
	VectorBase &operator-= (const VectorBase &op2);
	VectorBase &operator*= (Kernel op2);
	VectorBase &operator/= (Kernel op2);
};

template <class Kernel, unsigned int Components>
Kernel VectorBase<Kernel,Components>::Dot (const VectorBase<Kernel,Components> &op2) const
{
	Kernel result {};
	for (unsigned int i = 0; i < Components; ++i)
	{
		result += (*this)[i] * op2[i];
	}
	return result;
}

template<class Kernel>
Kernel VectorBase<Kernel, 2>::Dot(const VectorBase<Kernel, 2> &op2) const
{ return X*op2.X + Y *op2.Y; }

template<class Kernel>
Kernel VectorBase<Kernel, 3>::Dot(const VectorBase<Kernel, 3> &op2) const
{ return X*op2.X + Y *op2.Y + Z * op2.Z; }

template<class Kernel>
Kernel VectorBase<Kernel, 4>::Dot(const VectorBase<Kernel, 4> &op2) const
{ return X*op2.X + Y *op2.Y + Z * op2.Z + W * op2.W; }


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////Length//////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel,Components>::Length () const
{
	FloatingPointKernel<Kernel>::Type result {};

	for (unsigned int i = 0; i < Components; ++i)
	{
		result += FloatingPointKernel<Kernel>::Type((*this)[i]) * FloatingPointKernel<Kernel>::Type((*this[i]));
	}

	result = std::sqrt(result);
	return result;
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 2>::Length() const
{
	typedef typename FloatingPointKernel<Kernel>::Type r;
	return std::sqrt(r(X)*r(X) + r(Y)*r(Y));
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 3>::Length() const
{
	typedef typename FloatingPointKernel<Kernel>::Type r;
	return std::sqrt(r(X)*r(X) + r(Y)*r(Y) + r(Z)*r(Z));
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 4>::Length() const
{
	typedef typename FloatingPointKernel<Kernel>::Type r;
	return std::sqrt(r(X)*r(X) + r(Y)*r(Y) + r(Z)*r(Z) +r(W)*r(W));
}


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////LengthSquared///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel,Components>::LengthSquared () const
{
	FloatingPointKernel<Kernel>::Type result {};

	for (unsigned int i = 0; i < Components; ++i)
	{
		result += (*this)[i] * (*this[i]);
	}

	return result;
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 2>::LengthSquared() const
{
	typedef typename FloatingPointKernel<Kernel>::Type r;
	return (r(X)*r(X) + r(Y)*r(Y));
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 3>::LengthSquared() const
{
	typedef typename FloatingPointKernel<Kernel>::Type r;
	return (r(X)*r(X) + r(Y)*r(Y) + r(Z)*r(Z));
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 4>::LengthSquared() const
{
	typedef typename FloatingPointKernel<Kernel>::Type r;
	return (r(X)*r(X) + r(Y)*r(Y) + r(Z)*r(Z) + r(W)*r(W));
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////Distance////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel,Components>::Distance (const VectorBase<Kernel,Components> &op2) const
{
	return ((*this) - op2).Length ();
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 2>::Distance(const VectorBase<Kernel, 2> &op2) const
{
	return ((*this) - op2).Length();
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 3>::Distance(const VectorBase<Kernel, 3> &op2) const
{
	return ((*this) - op2).Length();
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 4>::Distance(const VectorBase<Kernel, 4> &op2) const
{
	return ((*this) - op2).Length();
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////DistanceSquared/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, Components>::DistanceSquared(const VectorBase<Kernel, Components> &op2) const
{
	return ((*this) - op2).LengthSquared ();
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 2>::DistanceSquared(const VectorBase<Kernel, 2> &op2) const
{
	return ((*this) - op2).LengthSquared();
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 3>::DistanceSquared(const VectorBase<Kernel, 3> &op2) const
{
	return ((*this) - op2).LengthSquared();
}

template<class Kernel>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel, 4>::DistanceSquared(const VectorBase<Kernel, 4> &op2) const
{
	return ((*this) - op2).LengthSquared();
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////WithinDistance//////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
bool VectorBase<Kernel,Components>::WithinDistance (const VectorBase<Kernel,Components> &point, typename FloatingPointKernel<Kernel>::Type distance) const
{
	return Distance (point) <= distance;
}

template<class Kernel>
bool VectorBase<Kernel, 2>::WithinDistance(const VectorBase<Kernel, 2> &point, typename FloatingPointKernel<Kernel>::Type distance) const
{
	return Distance(point) <= distance;
}

template<class Kernel>
bool VectorBase<Kernel, 3>::WithinDistance(const VectorBase<Kernel, 3> &point, typename FloatingPointKernel<Kernel>::Type distance) const
{
	return Distance(point) <= distance;
}

template<class Kernel>
bool VectorBase<Kernel, 4>::WithinDistance(const VectorBase<Kernel, 4> &point, typename FloatingPointKernel<Kernel>::Type distance) const
{
	return Distance(point) <= distance;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////Normalized//////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> VectorBase<Kernel,Components>::Normalized () const
{
	VectorBase<Kernel,Components> result (*this);
	result /= result.Length ();
	return result;
}

template<class Kernel>
VectorBase<Kernel, 2> VectorBase<Kernel, 2>::Normalized() const
{
	VectorBase<Kernel, 2> result(*this);
	result /= result.Length();
	return result;
}

template<class Kernel>
VectorBase<Kernel, 3> VectorBase<Kernel, 3>::Normalized() const
{
	VectorBase<Kernel, 3> result(*this);
	result /= result.Length();
	return result;
}

template<class Kernel>
VectorBase<Kernel, 4> VectorBase<Kernel, 4>::Normalized() const
{
	VectorBase<Kernel, 4> result(*this);
	result /= result.Length();
	return result;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////Normalize///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::Normalize ()
{
	(*this) /= Length();
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 2> &VectorBase<Kernel, 2>::Normalize()
{
	(*this) /= Length();
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 3> &VectorBase<Kernel, 3>::Normalize()
{
	(*this) /= Length();
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 4> &VectorBase<Kernel, 4>::Normalize()
{
	(*this) /= Length();
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////operator+=///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator+= (const VectorBase<Kernel,Components> &op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] += op2[i];
	}
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 2> &VectorBase<Kernel, 2>::operator+= (const VectorBase<Kernel, 2> &op2)
{
	X += op2.X;
	Y += op2.Y;
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 3> &VectorBase<Kernel, 3>::operator+= (const VectorBase<Kernel, 3> &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 4> &VectorBase<Kernel, 4>::operator+= (const VectorBase<Kernel, 4> &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	W += op2.W;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////operator-=///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator-= (const VectorBase<Kernel,Components> &op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] -= op2[i];
	}
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 2> &VectorBase<Kernel, 2>::operator-= (const VectorBase<Kernel, 2> &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 3> &VectorBase<Kernel, 3>::operator-= (const VectorBase<Kernel, 3> &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 4> &VectorBase<Kernel, 4>::operator-= (const VectorBase<Kernel, 4> &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	W -= op2.W;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////operator*=///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator*= (Kernel op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] *= op2;
	}
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 2> &VectorBase<Kernel, 2>::operator*= (Kernel op2)
{
	X *= op2;
	Y *= op2;
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 3> &VectorBase<Kernel, 3>::operator*= (Kernel op2)
{
	X *= op2;
	Y *= op2;
	Z *= op2;
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 4> &VectorBase<Kernel, 4>::operator*= (Kernel op2)
{
	X *= op2;
	Y *= op2;
	Z *= op2;
	W *= op2;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
////////////////////////operator/=///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator/= (Kernel op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] /= op2;
	}
	return *this;
}

template<class Kernel>
VectorBase<Kernel, 2> &VectorBase<Kernel, 2>::operator/= (Kernel op2)
{
	X /= op2;
	Y /= op2;
	return *this;
}
template<class Kernel>
VectorBase<Kernel, 3> &VectorBase<Kernel, 3>::operator/= (Kernel op2)
{
	X /= op2;
	Y /= op2;
	Z /= op2;
	return *this;
}
template<class Kernel>
VectorBase<Kernel, 4> &VectorBase<Kernel, 4>::operator/= (Kernel op2)
{
	X /= op2;
	Y /= op2;
	Z /= op2;
	W /= op2;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> operator- (const VectorBase<Kernel,Components> &op1, const VectorBase<Kernel,Components> &op2)
{
	VectorBase<Kernel,Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = op1[i] - op2[1];
	}

	return result;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> operator+ (const VectorBase<Kernel,Components> &op1, const VectorBase<Kernel,Components> &op2)
{
	VectorBase<Kernel,Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = op1[i] + op2[1];
	}

	return result;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> operator* (const VectorBase<Kernel,Components> &op1, Kernel op2)
{
	VectorBase<Kernel,Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = op1[i] * op2;
	}

	return result;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> operator* (Kernel op1, const VectorBase<Kernel,Components> &op2)
{
	VectorBase<Kernel,Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = op1 * op2[1];
	}

	return result;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> operator/ (const VectorBase<Kernel,Components> &op1, Kernel op2)
{
	VectorBase<Kernel,Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = op1[1] / op2;
	}

	return result;
}

template <class Kernel, unsigned int Components>
typename std::enable_if <HasOStreamOperator<Kernel>::Value, std::ostream>::type &operator<< (std::ostream &stream, const VectorBase<Kernel,Components> &vec)
{
	stream << "<";

	for (unsigned int i = 0; i < Components; ++i)
	{
		stream << vec[i];
		if (i != Components - 1)
		{
			stream << ", ";
		}
	}

	stream << ">";

	return stream;
}

template<class Kernel, unsigned int Components>
VectorBase<Kernel, Components> Clamp(const VectorBase<Kernel, Components> &value, const VectorBase<Kernel, Components> &min, const VectorBase<Kernel, Components> &max)
{
	Tocs::Math::VectorBase<Kernel, Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = Clamp(value[i], min[i], max[i]);
	}

	return result;
}

typedef VectorBase<float, 2> Vector2;
typedef VectorBase<float, 3> Vector3;
typedef VectorBase<float, 4> Vector4;

typedef VectorBase<int, 2> Vector2i;
typedef VectorBase<int, 3> Vector3i;
typedef VectorBase<int, 4> Vector4i;

typedef VectorBase<unsigned int, 2> Vector2ui;
typedef VectorBase<unsigned int, 3> Vector3ui;
typedef VectorBase<unsigned int, 4> Vector4ui;

}}

namespace std {

template <class Kernel, unsigned int Components>
Tocs::Math::VectorBase<Kernel, Components> min(const Tocs::Math::VectorBase<Kernel, Components> &a, const Tocs::Math::VectorBase<Kernel, Components> &b)
{
	Tocs::Math::VectorBase<Kernel, Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = std::min(a[i], b[i]);
	}

	return result;
}

template <class Kernel, unsigned int Components>
Tocs::Math::VectorBase<Kernel, Components> max(const Tocs::Math::VectorBase<Kernel, Components> &a, const Tocs::Math::VectorBase<Kernel, Components> &b)
{
	Tocs::Math::VectorBase<Kernel, Components> result;

	for (unsigned int i = 0; i < Components; ++i)
	{
		result[i] = std::max(a[i], b[i]);
	}

	return result;
}

}