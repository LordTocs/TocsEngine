#pragma once
#include <utility>

namespace Tocs {
namespace Componentry {

class IAttribute
{
public:
	virtual ~IAttribute ();
};

template <class T>
class Attribute
{
	T Value;
	bool Changed;
public:
	Attribute ()
		:  Value(T ()),
		   Changed(false)
	{
	}
	Attribute (const T& value)
		: Value (value),
		  Changed(false)
	{}

	Attribute (T&& value)
		: Value(std::forward<T> (value)),
		  Changed(false)
	{}

	Attribute<T> &operator= (const T& value)
	{
		Value = value;
		Changed = true;
		return *this;
	}

	Attribute<T> &operator= (T && value)
	{
		Value = std::forward<T> (value);
		Changed = true;
	}

	operator T &()
	{
		return Value;
	}

	operator const T &() const
	{
		return Value;
	}

};

}}