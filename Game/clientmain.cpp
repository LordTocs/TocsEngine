#include <iostream>
#include <utility>
#include <Tocs/Core/PackedFreeList.h>
#include "Game.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Core/Ticker.h>
#include <Tocs/Core/StackTrace.h>
#include <Tocs/Math/Vector.h>
#include <Tocs/Rendering/Material.h>



using namespace Tocs;
using namespace Tocs::Math;
using namespace Tocs::Rendering;
using namespace std;

class Test
{
public:
	Test()
	{
		cout << "Test()" << endl;
	}
	Test(const Test &)
	{
		cout << "Test(const Test &)" << endl;
	}
	Test(Test &&)
	{
		cout << "Test(Test &&)" << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
};
void dotest()
{
	cout << "===Construct===" << endl;
	PackedFreeList <Test> TestList;
	cout << "===Add===" << endl;
	auto a = TestList.Add(Test());
	auto b = TestList.Add(Test());
	cout << "===Ret===" << endl;
	TestList.Get(a);
	TestList.Get(b);
	cout << "=========" << endl;
}
/*
int main()
{
	dotest();
	int pause;
	cin >> pause;
	return 0;
}*/


int main ()
{
	dotest();
	cout << endl;
	Game game;
	game.Start();
}