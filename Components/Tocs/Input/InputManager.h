#pragma once
#include "Mouse.h"
#include "Keyboard.h"
namespace Tocs {
namespace Input	{

class InputManager
{
public:
	Mouse Mouse;
	Keyboard Keyboard;

	void Update (float dt);
};

}}

