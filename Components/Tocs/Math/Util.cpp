#include "Util.h"
#include <mmintrin.h>


namespace Tocs {
namespace Math {
/*
static float minss ( float a, float b )
{
    // Branchless SSE min.
    _mm_store_ss( &a, _mm_min_ss(_mm_set_ss(a),_mm_set_ss(b)) );
    return a;
}

static float maxss ( float a, float b )
{
    // Branchless SSE max.
    _mm_store_ss( &a, _mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)) );
    return a;
}


float Clamp (float value, float min, float max)
{
	_mm_store_ss( &value, _mm_min_ss( _mm_max_ss(_mm_set_ss(val),_mm_set_ss(minval)), _mm_set_ss(maxval) ) );
    return val;
}
*/

}}