#include <iostream>
#include <utility>
#include <Tocs/Core/PackedFreeList.h>
//#include "Game.h"
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Input/SimpleWindow.h>
#include <Tocs/Core/Ticker.h>
#include <Tocs/Core/StackTrace.h>

using namespace Tocs;
using namespace std;

void C () { StackTrace trace; trace.PrettyPrint (); }
void B () { C (); }
void A () { B (); }

int main ()
{
	A();

	Input::SimpleWindow Window("Tocs Engine",1000,1000,false,false);
	Graphics::GraphicsContext GContext(Window);
	Ticker GameTick;
	while (!Window.IsExiting ())
	{
		Window.PumpMessages();
		GContext.ClearActiveBuffer();
		float dt = GameTick.GetTickTime();
		Window.Input.Update(dt);
		GContext.FlipToScreen();
	}

	//Game game;
	//game.Start();

	/*PackedFreeList<int> test;

	auto one = test.Add(1);
	auto two = test.Add(2);
	auto three = test.Add(3);
	auto four = test.Add(4);


	std::cout << "One: " << test.Get(one) << std::endl;
	std::cout << "Two: " << test.Get(two) << std::endl;
	std::cout << "Three: " << test.Get(three) << std::endl;
	std::cout << "Four: " << test.Get(four) << std::endl;

	test.Remove(two);
	std::cout << std::endl;
	std::cout << "One: " << test.Get(one) << std::endl;
	std::cout << "Three: " << test.Get(three) << std::endl;
	std::cout << "Four: " << test.Get(four) << std::endl;
	std::cout << std::endl;
	for (auto i = test.BeginObjects(); i != test.EndObjects (); ++i)
	{
		std::cout << "Iter: " << (*i) << std::endl;
	}
	std::cout << std::endl;

	test.Sort ();

	std::cout << std::endl;
	for (auto i = test.BeginObjects(); i != test.EndObjects (); ++i)
	{
		std::cout << "Iter: " << (*i) << std::endl;
	}
	std::cout << std::endl;
	std::cout << "One: " << test.Get(one) << std::endl;
	std::cout << "Three: " << test.Get(three) << std::endl;
	std::cout << "Four: " << test.Get(four) << std::endl;*/

}