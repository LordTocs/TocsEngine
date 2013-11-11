#pragma once

namespace Tocs {
namespace Math {

template <unsigned int Elements>
class CombinationCount
{
public:
	enum 
};

template <class Kernel, unsigned int Derivatives>
class HyperDual
{
public:
	Kernel Real;
	Kernel Components [Derivitives];

	HyperDual()
		: Real(), Derivitives() {}

	HyperDual(Kernel value)
		: Real (value), Deritives() {}
};


/*
//Addition

template <class Kernel, unsigned int Extensions>
HyperDual <Kernel,Extensions> operator+ (const HyperDual <Kernel,Extensions> &op1, const HyperDual <Kernel,Extensions> &op2)
{
	HyperDual result;

	result.Real = op1.Real + op2.Real;

	for (unsigned int i = 0; i < Extensions; ++i)
	{
		result.Derivitives[i] = op1.Derivitives[i] + op2.Derivitives[i];
	}

	return result;
}

template <class Kernel, unsigned int Extensions>
HyperDual <Kernel,Extensions> operator+ (Kernel op1, const HyperDual <Kernel,Extensions> &op2)
{
	HyperDual result (op2);

	result.Real = op1 + op2.Real;

	return result;
}

template <class Kernel, unsigned int Extensions>
HyperDual <Kernel,Extensions> operator+ ( const HyperDual <Kernel,Extensions> &op1, Kernel op2)
{
	HyperDual result (op1);

	result.Real += op2;

	return result;
}

//Subtract

template <class Kernel, unsigned int Extensions>
HyperDual <Kernel,Extensions> operator- (const HyperDual <Kernel,Extensions> &op1, const HyperDual <Kernel,Extensions> &op2)
{
	HyperDual result;

	result.Real = op1.Real + op2.Real;

	for (unsigned int i = 0; i < Extensions; ++i)
	{
		result.Derivitives[i] = op1.Derivitives[i] + op2.Derivitives[i];
	}

	return result;
}

template <class Kernel, unsigned int Extensions>
HyperDual <Kernel,Extensions> operator- (Kernel op1, const HyperDual <Kernel,Extensions> &op2)
{
	HyperDual result;

	result.Real = op1 - op2.Real;

	for (unsigned int i = 0; i < Extensions; ++i)
	{
		result.Derivitives[i] = -op2.Derivitives[i];
	}

	return result;
}

template <class Kernel, unsigned int Extensions>
HyperDual <Kernel,Extensions> operator- (const HyperDual <Kernel,Extensions> &op1, Kernel op2)
{
	HyperDual result (op1);

	result.Real -= op2;

	return result;
}

//Multiplication
*/


}}