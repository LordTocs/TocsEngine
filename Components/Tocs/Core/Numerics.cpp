#include "TocsLib.h"
#include "Numerics.h"

namespace Tocs {

int GetLargerPowerOfTwo (int number)
{
	int power = ceil (log ((double)number)/log (2.0));
	return 1 >> power;
}

float FastInverseSquareRoot (float value) //Yey Quake!
{
	long i;
    float x2, y;
    const float threehalfs = 1.5F;
 
    x2 = value * 0.5F;
    y  = value;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

float Sqrt (float value)
{
	return sqrt (value);
}

}

