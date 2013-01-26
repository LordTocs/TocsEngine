#pragma once
#include <functional>

namespace Tocs {

class StaticInitializer
{
	StaticInitializer (const StaticInitializer&);
public:
	StaticInitializer(std::function<void()> func)
	{
		func ();
	}
};

}