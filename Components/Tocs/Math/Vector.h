#pragma once
#include <type_traits>
#include <cmath>
#include <Tocs/Core/MemberChecks.h>

namespace Tocs {
namespace Math {

template <class Kernel>
class FloatingPointKernel;

class FloatingPointKernel<int>
{
public:
	typedef float Type;
};

class FloatingPointKernel<unsigned int>
{
public:
	typedef float Type;
};

class FloatingPointKernel<short>
{
public:
	typedef float Type;
};

class FloatingPointKernel<unsigned short>
{
public:
	typedef float Type;
};

class FloatingPointKernel<float>
{
public:
	typedef float Type;
};

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

	Kernel &operator[] (unsigned int i) const
	{ return Data[i]; }

	const Kernel &operator[] (unsigned int i) const
	{ return Data[i]; }

	Kernel Dot (const VectorBase &op2);

	FloatingPointKernel<Kernel>::Type Length () const;
	FloatingPointKernel<Kernel>::Type LengthSquared () const;
	FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, FloatingPointKernel<Kernel>::Type distance) const;

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
	{ X = x; Y = y; }

	Kernel &operator[] (unsigned int i)
	{ return *(&X + i); }

	const Kernel &operator[] (unsigned int i) const
	{ return *(&X + i); }

	Kernel Dot (const VectorBase &op2); //{ return VectorBase(X * op2.X, Y * op2.Y, Z * op2.Z); }

	Kernel Cross (const VectorBase &op2)
	{
		return (X * op2.Y) - (X * op1.Y);
	}

	FloatingPointKernel<Kernel>::Type Length () const;
	FloatingPointKernel<Kernel>::Type LengthSquared () const;
	FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, FloatingPointKernel<Kernel>::Type distance) const;

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
	{ X = x; Y = y; Z = z; }

	Kernel &operator[] (unsigned int i)
	{ return *(&X + i); }

	const Kernel &operator[] (unsigned int i) const
	{ return *(&X + i); }

	Kernel Dot (const VectorBase &op2); //{ return VectorBase(X * op2.X, Y * op2.Y, Z * op2.Z); }

	VectorBase Cross (const VectorBase &op2)
	{
		VectorBase result;
		result.X =  (Y * op2.Z) - (Y * op1.Z);
		result.Y = -((X * op2.Z) - (X * op1.Z));
		result.Z =  (X * op2.Y) - (X * op1.Y);
		return result;
	}

	FloatingPointKernel<Kernel>::Type Length () const;
	FloatingPointKernel<Kernel>::Type LengthSquared () const;
	FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, FloatingPointKernel<Kernel>::Type distance) const;

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
	{ X = x; Y = y; Z = z; W = w;}

	Kernel &operator[] (unsigned int i)
	{ return *(&X + i); }

	const Kernel &operator[] (unsigned int i) const
	{ return *(&X + i); }

	Kernel Dot (const VectorBase &op2); //{ return VectorBase(X * op2.X, Y * op2.Y, Z * op2.Z); }

	VectorBase Cross (const VectorBase &op2)
	{
		VectorBase result;
		result.X =  (Y * op2.Z) - (Y * op1.Z);
		result.Y = -((X * op2.Z) - (X * op1.Z));
		result.Z =  (X * op2.Y) - (X * op1.Y);
		return result;
	}

	FloatingPointKernel<Kernel>::Type Length () const;
	FloatingPointKernel<Kernel>::Type LengthSquared () const;
	FloatingPointKernel<Kernel>::Type Distance (const VectorBase &op2) const;
	FloatingPointKernel<Kernel>::Type DistanceSquared (const VectorBase &op2) const;
	bool WithinDistance (const VectorBase &point, FloatingPointKernel<Kernel>::Type distance) const;

	bool operator== (const VectorBase &op2) const;
	bool operator!= (const VectorBase &op2) const;

	VectorBase &operator+= (const VectorBase &op2);
	VectorBase &operator-= (const VectorBase &op2);
	VectorBase &operator*= (Kernel op2);
	VectorBase &operator/= (Kernel op2);
};

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> VectorBase<Kernel,Components>::Dot (const VectorBase<Kernel,Components> &op2)
{
	Kernel result {};
	for (unsigned int i = 0; i < Components; ++i)
	{
		result += (*this)[i] * op2[i];
	}
	return result;
}

template <class Kernel, unsigned int Components>
typename FloatingPointKernel<Kernel>::Type VectorBase<Kernel,Components>::Length () const
{
	FloatingPointKernel<Kernel>::Type result {};

	for (unsigned int i = 0; i < Components; ++i)
	{
		result += (*this)[i] * (*this[i]);
	}

	result = std::sqrt(result);
	return result;
}


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

template <class Kernel, unsigned int Components>
FloatingPointKernel<Kernel>::Type VectorBase<Kernel,Components>::Distance (const VectorBase<Kernel,Components> &op2) const
{
	return ((*this) - op2).Length ();
}

template <class Kernel, unsigned int Components>
FloatingPointKernel<Kernel>::Type VectorBase<Kernel,Components>::DistanceSquared (const VectorBase<Kernel,Components> &op2) const
{
	return ((*this) - op2).LengthSquared ();
}

template <class Kernel, unsigned int Components>
bool VectorBase<Kernel,Components>::WithinDistance (const VectorBase<Kernel,Components> &point, FloatingPointKernel<Kernel>::Type distance) const
{
	return Distance (point) <= distance;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator+= (const VectorBase<Kernel,Components> &op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] += op2[i];
	}
	return *this;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator-= (const VectorBase<Kernel,Components> &op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] -= op2[i];
	}
	return *this;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator*= (Kernel op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] *= op2;
	}
	return *this;
}

template <class Kernel, unsigned int Components>
VectorBase<Kernel,Components> &VectorBase<Kernel,Components>::operator/= (Kernel op2)
{
	for (unsigned int i = 0; i < Components; ++i)
	{
		(*this)[i] /= op2;
	}
	return *this;
}

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
std::enable_if <HasOStreamOperator<Kernel>::Value, std::ostream>::type &operator<< (std::ostream &stream, const VectorBase<Kernel,Components> &vec)
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

}}