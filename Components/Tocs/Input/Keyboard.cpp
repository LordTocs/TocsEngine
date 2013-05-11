#include "Keyboard.h"
#include <Windows.h>

namespace Tocs {
namespace Input {

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		KeyTimes[i] = -1;
	}
}


void Keyboard::Update (float dt)
{
	for (int i = 0; i < 256; i++)
	{
		if ((GetAsyncKeyState(i) >> 8))
		{
			if (KeyTimes [i] < 0)
			{
				KeyTimes[i] = 0;
			}
			else
			{
				KeyTimes[i] += dt;
			}
		}
		else
		{
			KeyTimes[i] = -1;
		}
	}
}

bool Keyboard::IsPressed (int key)
{
	if (key < 0 || key > 255)
		return false;

	return KeyTimes[key] >= 0;
}

bool Keyboard::IsNewlyPressed (int key)
{
	if (key < 0 || key > 255)
		return false;

	return KeyTimes[key] == 0;
}

bool Keyboard::IsRepeatedlyPressed (int key)
{
	if (key < 0 || key > 255)
		return false;

	return KeyTimes[key] >= 0;
}

}}