#pragma once
#include "Vector.h"
#include "Promotion.h"
#include <cmath>
namespace Tocs {
namespace Math {

template <class Kernel>
class QuaternionBase
{
public:
	Kernel X, Y, Z, W;
	QuaternionBase()
		: X(), Y(), Z(), W() {}
	QuaternionBase(Kernel x, Kernel y, Kernel z, Kernel w)
		: X(x), Y(y), Z(z), W(w) {}

	typename ToReal<Kernel>::Type Magnitude() const
	{
		return std::sqrt<ToReal<Kernel>::Type>(X*X + Y*Y + Z*Z + W*W);
	}
	QuaternionBase<Kernel> &Normalize()
	{
		auto len = Magnitude();
		X /= len;
		Y /= len;
		Z /= len;
		W /= len;
		return *this;
	}

	VectorBase<Kernel,3> RotateVector(VectorBase<Kernel,3> v) const
	{
		QuaternionBase<Kernel> result = (*this) * PureQuaternion(v) * Conjugate();
		return VectorBase<Kernel, 3>(result.X, result.Y, result.Z);
	}

	Kernel Dot(const QuaternionBase<Kernel> &op2) const
	{
		return X * op2.X + Y * op2.Y + Z * op2.Z + W * op2.W;
	}

	static QuaternionBase<Kernel> Slerp(const QuaternionBase &start, const QuaternionBase &finish, typename ToReal<Kernel>::Type t)
	{
		typename ToReal<Kernel>::Type theta = std::acos(start.Dot(finish));
		return start * (sin((1 - t) * theta) / sin(theta)) + finish * (sin(t * theta) / sin(theta));
	}
	static QuaternionBase<Kernel> FromEuler(typename ToReal<Kernel>::Type x, typename ToReal<Kernel>::Type y, typename ToReal<Kernel>::Type z)
	{
		QuaternionBase Qx, Qy, Qz;
		Qx.W = std::cos(x / 2);
		Qx.X = std::sin(x / 2);
		Qy.W = std::cos(y / 2);
		Qy.Y = std::sin(y / 2);
		Qz.W = std::cos(z / 2);
		Qz.Z = std::sin(z / 2);
		return Qx * Qy * Qz;
	}

	static QuaternionBase<Kernel> PureQuaternion(const VectorBase<Kernel,3> &vector)
	{
		return QuaternionBase<Kernel>(vector.X, vector.Y, vector.Z, 0);
	}

	static QuaternionBase<Kernel> FromEuler(const VectorBase<typename ToReal<Kernel>::Type,3> &euler)
	{
		QuaternionBase Qx, Qy, Qz;
		Qx.W = std::cos(euler.x / 2);
		Qx.X = std::sin(euler.x / 2);
		Qy.W = std::cos(euler.y / 2);
		Qy.Y = std::sin(euler.y / 2);
		Qz.W = std::cos(euler.z / 2);
		Qz.Z = std::sin(euler.z / 2);
		return Qx * Qy * Qz;
	}

	const static QuaternionBase<Kernel> Identity;

	QuaternionBase<Kernel> &operator+= (const QuaternionBase<Kernel> &op2)
	{
		X += op2.X;
		Y += op2.Y;
		Z += op2.Z;
		W += op2.W;
	}
	QuaternionBase<Kernel> &operator-= (const QuaternionBase<Kernel> &op2)
	{
		X -= op2.X;
		Y -= op2.Y;
		Z -= op2.Z;
		W -= op2.W;
	}
	QuaternionBase<Kernel> &operator*= (const QuaternionBase<Kernel> &op2)
	{
		W = W*op2.W - X*op2.X - Y*op2.Y - Z*op2.Z;
		X = W*op2.X + X*op2.W + Y*op2.Z - Z*op2.Y;
		Y = W*op2.Y - X*op2.Z + Y*op2.W + Z*op2.X;
		Z = W*op2.Z + X*op2.Y - Y*op2.X + Z*op2.W;
	}
	QuaternionBase<Kernel> &operator/= (const QuaternionBase<Kernel> &op2)
	{
		Kernel denom = op2.Dot(op2);
		X = (X * op2.X + Y * op2.Y + Z * op2.Z + W * op2.W) / denom;
		Y = (X * op2.X - Y * op2.Y - Z * op2.Z + W * op2.W) / denom;
		Z = (X * op2.X + Y * op2.Y - Z * op2.Z - W * op2.W) / denom;
		W = (X * op2.X - Y * op2.Y + Z * op2.Z - W * op2.W) / denom;
		return *this;

	}
	QuaternionBase<Kernel> &operator*= (const Kernel &op2)
	{
		X *= op2.X;
		Y *= op2.Y;
		Z *= op2.Z;
		W *= op2.W;
	}
	QuaternionBase<Kernel> &operator/= (const Kernel &op2)
	{
		X /= op2.X;
		Y /= op2.Y;
		Z /= op2.Z;
		W /= op2.W;
	}

	QuaternionBase<Kernel> Conjugate() const
	{
		return QuaternionBase(X, -Y, -Z, -W);
	}

	QuaternionBase<Kernel> Inverse() const
	{
		return Conjugate() / (Dot(*this));
	}


};

template<class Kernel>
const QuaternionBase <Kernel> QuaternionBase<Kernel>::Identity(Kernel(), Kernel(), Kernel(), Kernel(1));

template <class Kernel>
QuaternionBase<Kernel> operator*(const QuaternionBase<Kernel> &op1, const QuaternionBase<Kernel> &op2)
{
	QuaternionBase<Kernel> result;
	result.W = op1.W*op2.W - op1.X*op2.X - op1.Y*op2.Y - op1.Z*op2.Z;
	result.X = op1.W*op2.X + op1.X*op2.W + op1.Y*op2.Z - op1.Z*op2.Y;
	result.Y = op1.W*op2.Y - op1.X*op2.Z + op1.Y*op2.W + op1.Z*op2.X;
	result.Z = op1.W*op2.Z + op1.X*op2.Y - op1.Y*op2.X + op1.Z*op2.W;
	return result;
}

template <class Kernel>
QuaternionBase<Kernel> operator*(const Kernel &op1, const QuaternionBase<Kernel> &op2)
{
	QuaternionBase<Kernel> result;
	result.W = op2.W * op1;
	result.X = op2.X * op1;
	result.Y = op2.Y * op1;
	result.Z = op2.Z * op1;
	return result;
}

template <class Kernel>
QuaternionBase<Kernel> operator*(const QuaternionBase<Kernel> &op1, const Kernel &op2)
{
	QuaternionBase<Kernel> result;
	result.W = op2 * op1.W;
	result.X = op2 * op1.X;
	result.Y = op2 * op1.Y;
	result.Z = op2 * op1.Z;
	return result;
}

template <class Kernel>
VectorBase<Kernel, 3> operator*(const QuaternionBase<Kernel> &op1, const VectorBase<Kernel, 3> &op2)
{
	VectorBase<Kernel, 3> u(op1.X, op1.Y, op1.Z);
	VectorBase<Kernel, 3> uv = u.Cross(op2) * op1.W;
	VectorBase<Kernel, 3> uuv = u.Cross(uv);

	return op2 + (uv + uuv) * Kernel(2);
}
template <class Kernel>
VectorBase<Kernel, 3> operator*(const VectorBase<Kernel, 3> &op1, const QuaternionBase<Kernel> &op2)
{
	return op2.Inverse() * op1;
}

template <class Kernel>
QuaternionBase<Kernel> operator/(const QuaternionBase<Kernel> &op1, const Kernel &op2)
{
	QuaternionBase<Kernel> result;
	result.W = op1.W / op2;
	result.X = op1.X / op2;
	result.Y = op1.Y / op2;
	result.Z = op1.Z / op2;
	return result;
}
template <class Kernel>
QuaternionBase<Kernel> operator/(const QuaternionBase<Kernel> &op1, const QuaternionBase<Kernel> &op2)
{
	Quaternion result;
	Kernel denom = op2.Dot(op2);
	result.X = (op1.X * op2.X + op1.Y * op2.Y + op1.Z * op2.Z + op1.W * op2.W) / denom;
	result.Y = (op1.X * op2.X - op1.Y * op2.Y - op1.Z * op2.Z + op1.W * op2.W) / denom;
	result.Z = (op1.X * op2.X + op1.Y * op2.Y - op1.Z * op2.Z - op1.W * op2.W) / denom;
	result.W = (op1.X * op2.X - op1.Y * op2.Y + op1.Z * op2.Z - op1.W * op2.W) / denom;
	return result;
}

template <class Kernel>
QuaternionBase<Kernel> operator+(const QuaternionBase<Kernel> &op1, const QuaternionBase<Kernel> &op2)
{
	QuaternionBase<Kernel> result;
	result.W = op1.W + op2.W;
	result.X = op1.X + op2.X;
	result.Y = op1.Y + op2.Y;
	result.Z = op1.Z + op2.Z;
	return result;
}
template <class Kernel>
QuaternionBase<Kernel> operator-(const QuaternionBase<Kernel> &op1, const QuaternionBase<Kernel> &op2)
{
	QuaternionBase<Kernel> result;
	result.W = op1.W - op2.W;
	result.X = op1.X - op2.X;
	result.Y = op1.Y - op2.Y;
	result.Z = op1.Z - op2.Z;
	return result;
}

template <class Kernel>
QuaternionBase<Kernel> operator-(const QuaternionBase<Kernel> &op1)
{
	return QuaternionBase<Kernel>(-op1.X, -op1.Y, -op1.Z, -op1.W);
}


typedef QuaternionBase<float> Quaternion;

template <class Kernel>
typename std::enable_if <HasOStreamOperator<Kernel>::Value, std::ostream>::type &operator<< (std::ostream &stream, const QuaternionBase<Kernel> &q)
{
	stream << "<" << q.X << ", " << q.Y << ", " << q.Z << ", " << q.W <<">";
	return stream;
}

}}