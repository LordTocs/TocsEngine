#pragma once

namespace Tocs {
namespace Math {

template <unsigned int N>
class Factorial
{
public:
	enum { Value = N * Factoria<N - 1>::Value};
};

template<>
class Factorial <0>
{
public:
	enum { Value = 1 };
};


template <unsigned int N, unsigned int K>
class BinomialCoefficient
{
public:
	enum { Value = Factorial<N>::Value / (Factorial<K>::Value * Factorial<N - K>::Value) };
};

}}
