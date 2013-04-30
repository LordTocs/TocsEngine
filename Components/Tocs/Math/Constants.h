#pragma once
#include <cmath>
namespace Tocs {
namespace Math {

class Constants
{
	Constants();
public:
	template <class T>
	static const T Pi ()
	{
		static T pi = std::atan(T(1))*4;
		return pi;
	}
};

}}