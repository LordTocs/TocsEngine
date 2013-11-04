#pragma once

namespace Tocs {
namespace Math {

template <class T>
T Clamp (T value, T min, T max)
{
	T result = (value < min ? min : value);
	result = (result > max ? max : result);
	return result;
}
/* //FUCK YOU SSE
float Clamp (float value, float min, float max);
*/

}}