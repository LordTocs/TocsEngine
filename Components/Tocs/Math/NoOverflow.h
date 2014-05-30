#pragma once
#include <limits>
#include <type_traits>
namespace Tocs {
namespace Math {

template <class integral_type>
class NoOverflow
{
	integral_type InternalValue;
public:
	NoOverflow() : InternalValue() { static_assert(std::is_integral<integral_type>::value, "NoOverflow only accepts integral types"); }
	NoOverflow(const integral_type value) : InternalValue(value) {}

	operator integral_type () const
	{
		return InternalValue;
	}

	NoOverflow &operator*= (const integral_type &op2)
	{
		if (!InternalValue || !op2)
			return *this;

		integral_type bound = ((InternalValue < 0) != (op2 < 0) ? std::numeric_limits<integral_type>::min() : std::numeric_limits<integral_type>::max());

		if (std::abs(bound / InternalValue) < abs(op2))
			InternalValue = bound;
		else
			InternalValue *= op2;
		
		return *this;
	}

	NoOverflow &operator+= (const integral_type &op2)
	{
		integral_type bound = (op2 > 0 ? std::numeric_limits<integral_type>::max() : std::numeric_limits<integral_type>::min());
		integral_type spaceleft = bound - op2;



		if ((op2 > 0) && (InternalValue > (std::numeric_limits<integral_type>::max() - op2)))
		{
			InternalValue = std::numeric_limits<integral_type>::max();
		}
		else if ((op2 < 0) && (InternalValue < (std::numeric_limits<integral_type>::min() - op2)))
		{
			InternalValue = std::numeric_limits<integral_type>::min();
		}
		else
		{
			InternalValue += op2;
		}
	}


};

}
}
