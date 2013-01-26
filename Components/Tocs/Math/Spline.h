#pragma once
#include <vector>


namespace Tocs {
namespace Math {
/*
template <class V, int degree, class F = float>
class BSpline
{
	std::vector<V> Points;
	std::vector<F> Knots

	std::vector<Knot> Knots;
	template <int d>
	F Boor(unsigned int i, F t)
	{
		return ((t - Knots[i])/(Knots[i + d] - Knots[i]))*Boor<d - 1>(i,t) + ((Knots[i + d + 1] - t)/(Knots[i + d + 1] - Knots[i + 1]))*Boor<d-1>(i+1,t);
	}

	template<>
	F Boor<0>(unsigned int i, F t)
	{
		if (t >= Knots[i] && t <= Knots[i] + 1)
		{
			return 1;
		}
		return 0;
	}

public:
	BSpline();
	
	void AddPoint (const V &point)
	{
		Points.push_back(point);
	}

	void AddKnot (const F knot)
	{
		Knots.push_back(point);
	}

	V operator()(F t)
	{
		V result;
		for (int i = 0; i < Knots.size () - degree - 2; ++i)
		{
			result += Point;
		}
	}
};
*/


}}
