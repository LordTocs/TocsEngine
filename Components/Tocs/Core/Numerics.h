#pragma once
#include "TocsAPI.h"
#include <math.h>
namespace Tocs {

template <class T>
T Min (T value1, T value2)
{
	if (value1 < value2)
	{
		return value1;
	}
	return value2;
}

template <class T>
T Clamp (T value, T min, T max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

TocsAPI float Sqrt (float value);
TocsAPI float FastInverseSquareRoot (float value);


TocsAPI int GetLargerPowerOfTwo (int number);


}