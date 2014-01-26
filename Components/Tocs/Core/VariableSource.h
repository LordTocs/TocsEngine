#pragma once

namespace Tocs {

template <class T>
class VariableSource
{
	union InternalStorage
	{
		T Value;
		T* Reference;
	};
	InternalStorage Internal;
	unsigned char Source;
public:
	VariableSource(T value)
		: Internal(value), Source(0)
	{}

	VariableSource(T *reference)
		: Internal(reference), Source(1)
	{}

	VariableSource &operator= (T value)
	{
		Internal.Value = value; Source = 0;
	}

	VariableSource &operator= (T *reference)
	{
		Internal.Reference = reference; Source = 1;
	}

	void Value(T value)
	{
		Internal.Value = value; Source = 0;
	}

	void Reference(T &reference)
	{
		Internal.Reference = &reference; Source = 1;
	}

	T &operator T ()
	{
		if (Source)
			return *Internal.Reference;
		else
			return Internal.Value;
	}
};

}