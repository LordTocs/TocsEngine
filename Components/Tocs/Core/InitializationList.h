#pragma once
#include <vector>
#include <functional>

namespace Tocs {

class InitializationList
{
	std::vector<std::function<void()>> InitList;
public:
	void Add (std::function<void()> func);

	void Init ();
};

}

