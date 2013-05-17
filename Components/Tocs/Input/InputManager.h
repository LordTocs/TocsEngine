#pragma once
#include "Mouse.h"
#include "Keyboard.h"
namespace Tocs {
namespace Input	{

class SimpleWindow;

class InputManager
{
public:
	InputManager(SimpleWindow &window)
		: Mouse(window)
	{}

	Mouse Mouse;
	Keyboard Keyboard;

	void Update (float dt);
};

}}

