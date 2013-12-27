#pragma once
#include <functional>
#include "InitializationList.h"
namespace Tocs {

template <class T>
class LateStatic
{
	T *Value;
	std::function<T ()> InitFunc;
public:
	LateStatic (std::function<T ()> initfunc)
		: Value(nullptr),
		  InitFunc(initfunc)
	{
	}

	LateStatic (std::function<T ()> initfunc, InitializationList &list)
		: Value(nullptr),
		  InitFunc(initfunc)
	{
		list.Add (std::bind (&LateStatic<T>::Init,this));
	}

	void Init ()
	{
		Value = new T (InitFunc ());
	}

	bool IsInit () const
	{
		return Value != nullptr;
	}

	T &Get () 
	{
		return *Value; 
	}

	const T&Get () const
	{
		return *Value;
	}
};
template<class T, T (*init) ()>
class FirstUseStatic
{
	T *Instance;
public:
	T &Get()
	{
		if (Instance == nullptr)
		{
			Instance = new T (std::move(init ()));
		}
		return *Instance;
	}
};

}
