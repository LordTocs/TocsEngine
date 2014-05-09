#pragma once

namespace Tocs {
namespace Math {

template <class Kernel>
class Dual
{
public:
	Kernel RealPart;
	Kernel DualPart;

	Dual() 
		: RealPart(), DualPart() {}
	Dual(const Kernel &real)
		: RealPart(real), DualPart () {}
	Dual(const Kernel &real, const Kernel &dual)
		: RealPart(real), DualPart(dual) {}

	

	Dual &operator+= (const Dual &b)
	{
		RealPart += b.RealPart;
		DualPart += b.DualPart;
		return *this;
	}
	Dual &operator+= (const Kernel &b)
	{
		RealPart += b;
		return *this;
	}
	Dual &operator-= (const Dual &b)
	{
		RealPart -= b.RealPart;
		DualPart -= b.DualPart;
		return *this;
	}
	Dual &operator-= (const Kernel &b)
	{
		RealPart -= b;
		return *this;
	}
	Dual &operator*= (const Dual &b)
	{
		RealPart *= b.RealPart;
		DualPart = (RealPart * b.DualPart + DualPart * b.RealPart);
		return *this;
	}
	Dual &operator*= (const Kernel &b)
	{
		RealPart *= b;
		DualPart *= b;
		return *this;
	}
	Dual &operator/= (const Dual &b)
	{
		RealPart /= b.RealPart;
		DualPart = (DualPart * b.RealPart - RealPart * b.DualPart) / (b.RealPart * b.RealPart);
		return *this;
	}
	Dual &operator/= (const Kernel &b)
	{
		RealPart /= b;
		DualPart /= b;
		return *this;
	}
	
	Dual Conjugate() const { return Dual(RealPart, -DualPart); }

};

///////////////////////////////////////////////////////////////
///////////////////Addition////////////////////////////////////
///////////////////////////////////////////////////////////////

template <class Kernel>
Dual<Kernel> operator+(const Dual<Kernel> &a, const Kernel &b)
{
	Dual result(a);
	result.RealPart += b;
	return result;
}

template <class Kernel>
Dual<Kernel> operator+(const Kernel &a, const Dual<Kernel> &b)
{
	Dual result(b);
	result.RealPart += a;
	return result;
}

template <class Kernel>
Dual<Kernel> operator+(const Dual<Kernel> &a, const Dual<Kernel> &b)
{
	Dual result;
	result.RealPart = a.RealPart + b.RealPart;
	result.DualPart = a.DualPart + b.DualPart;
	return result;
}

///////////////////////////////////////////////////////////////
///////////////////Subtraction/////////////////////////////////
///////////////////////////////////////////////////////////////

template <class Kernel>
Dual<Kernel> operator-(const Dual<Kernel> &a, const Kernel &b)
{
	Dual result(a);
	a.RealPart -= b;
	return result;
}

template <class Kernel>
Dual<Kernel> operator-(const Kernel &a, const Dual<Kernel> &b)
{
	Dual result(a);
	result.DualPart -= b.DualPart;
	result.RealPart -= b.RealPart;
	return result;
}

template <class Kernel>
Dual<Kernel> operator-(const Dual<Kernel> &a, const Dual<Kernel> &b)
{
	Dual result;
	result.RealPart = a.RealPart - b.RealPart;
	result.DualPart = a.DualPart - b.DualPart;
	return result;
}

///////////////////////////////////////////////////////////////
///////////////////Multiplication//////////////////////////////
///////////////////////////////////////////////////////////////

template <class Kernel>
Dual<Kernel> operator*(const Dual<Kernel> &a, const Kernel &b)
{
	Dual<Kernel> result(a);
	result.DualPart *= b;
	result.RealPart *= b;
	return result;
}

template <class Kernel>
Dual<Kernel> operator*(const Kernel &a, const Dual<Kernel> &b)
{
	Dual<Kernel> result(b);
	result.DualPart *= a;
	result.RealPart *= a;
	return result;
}

template <class Kernel>
Dual<Kernel> operator*(const Dual<Kernel> &a, const Dual<Kernel> &b)
{
	Dual<Kernel> result;
	result.RealPart = a.RealPart * b.RealPart;
	result.DualPart = (a.RealPart * b.DualPart + a.DualPart * b.RealPart);
	return result;
}

///////////////////////////////////////////////////////////////
///////////////////Division////////////////////////////////////
///////////////////////////////////////////////////////////////

template <class Kernel>
Dual<Kernel> operator/(const Dual<Kernel> &a, const Kernel &b)
{
	Dual<Kernel> result(a);
	result.DualPart /= b;
	result.RealPart /= b;
	return result;
}

template <class Kernel>
Dual<Kernel> operator/(const Kernel &a, const Dual<Kernel> &b)
{
	Dual<Kernel> result(a);
	result.RealPart /= b.RealPart;
	result.DualPart = -a*b.DualPart/(b.RealPart * b.RealPart);
	return result;
}

template <class Kernel>
Dual<Kernel> operator/(const Dual<Kernel> &a, const Dual<Kernel> &b)
{
	Dual<Kernel> result;
	result.RealPart = a.RealPart / b.RealPart;
	result.DualPart = (a.DualPart * b.RealPart - a.RealPart * b.DualPart) / (b.RealPart * b.RealPart);
	return result;
}

///////////////////////////////////////////////////////////////
///////////////////Other///////////////////////////////////////
///////////////////////////////////////////////////////////////

template <class Kernel>
Dual<Kernel> operator- (const Dual<Kernel> &a)
{
	Dual<Kernel> result;
	result.DualPart = -a.DualPart;
	result.RealPart = -a.RealPart;
	return result;
}

}}
