#pragma once
#include <Tocs/Math/CompileTimeNumerics.h>
namespace Tocs {
namespace Math {

template <unsigned int a, unsigned int b>
class HyperDualComponent
{
public:
	const static unsigned int Value = 1;
};

template <unsigned int a>
class HypderDualComponent <a, a>
{
public:
	const static unsigned int Value = 0;
};

template <unsigned int Elements>
class HyperDualComponentCount
{
	template <unsigned int iter>
	struct Counter
	{
		enum { Value = BinomialCoefficient<Elements,iter>::Value + Counter<iter-1>::Value };
	};

	template <>
	struct Counter <1>
	{
		enum { Value = Elements };
	};
public:
	enum { Value = Counter<Elements>::Value  };
};

template <class Kernel, unsigned int Derivatives>
class HyperDual
{

public:
	Kernel Components[HyperDualComponentCount<Derivatives>::Value + 1];

	HyperDual()
		: Real(), Derivitives(), ComponentCombinations(){}

	HyperDual(Kernel value)
		: Real(value), Deritives(), ComponentCombinations() {}

	Kernel &Real() { return Components[0]; }
	const Kernel &Real() const { return Components[0]; }
};


template<unsigned int Derivatives>
unsigned int[Derivatives] GetIndiceArray()
{
	unsigned int result[Derivatives];
	FillIndiceArray<Derivatives, 0, 1>(result);
	return result;
}

//Addition

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel, Derivitives> operator+ (const HyperDual <Kernel, Derivitives> &op1, const HyperDual <Kernel, Derivitives> &op2)
{
	HyperDual result;

	//result.Real = op1.Real + op2.Real;

	for (unsigned int i = 0; i < sizeof(Components) / sizeof(Kernel); ++i)
	{
		result.Components[i] = op1.Components[i] + op2.Components[i];
	}

	return result;
}

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel, Derivitives> operator+ (Kernel op1, const HyperDual <Kernel, Derivitives> &op2)
{
	HyperDual result (op2);

	result.Real() = op1.Real() + op2.Real();

	return result;
}

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel, Derivitives> operator+ (const HyperDual <Kernel, Derivitives> &op1, Kernel op2)
{
	HyperDual result (op1);

	result.Real() += op2.Real();

	return result;
}

//Subtract

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel, Derivitives> operator- (const HyperDual <Kernel, Derivitives> &op1, const HyperDual <Kernel, Derivitives> &op2)
{
	HyperDual result;

	for (unsigned int i = 0; i < sizeof(Components) / sizeof(Kernel); ++i)
	{
		result.Components[i] = op1.Components[i] - op2.Components[i];
	}

	return result;
}

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel,Derivitives> operator- (Kernel op1, const HyperDual <Kernel,Derivitives> &op2)
{
	HyperDual result;

	result.Real() = op1 - op2.Real();

	for (unsigned int i = 1; i < sizeof(Components) / sizeof(Kernel); ++i)
	{
		result.Components[i] = -op2.Components[i];
	}

	return result;
}

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel,Derivitives> operator- (const HyperDual <Kernel,Derivitives> &op1, Kernel op2)
{
	HyperDual result (op1);

	result.Real() -= op2;

	return result;
}

//Multiplication

template <class Kernel, unsigned int Derivitives>
HyperDual <Kernel, Derivitives> operator* (const HyperDual <Kernel, Derivitives> &op1, const HyperDual <Kernel, Derivitives> &op2)
{
	HyperDual<Kernel, Derivitives> result;

	result.Real() = op1.Real() * op2.Real();

	for (unsigned int i = 0; i < sizeof (Components)/sizeof(Kernel) - 1; ++i)
	{
		for (unsigned int j = 0; j < sizeof (Components) / sizeof(Kernel)-1; ++j)
		{

		}
	}

	return result;
}



}}