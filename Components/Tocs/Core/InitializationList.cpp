#include "InitializationList.h"


namespace Tocs {

void InitializationList::Add(std::function<void()> func)
{
	InitList.push_back(func);
}

void InitializationList::Init ()
{
	for (auto i = InitList.begin (); i != InitList.end (); ++i)
	{
		(*i)();
	}
}

}
