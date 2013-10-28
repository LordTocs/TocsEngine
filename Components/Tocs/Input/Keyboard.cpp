#include "Keyboard.h"
#define NOMINMAX
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
		if (KeyTimes[i] >= 0)
		{
			KeyTimes[i] += dt;
		}
	}
}

bool Keyboard::IsPressed (const Key &key)
{
	if (key.GetCode() < 0 || key.GetCode() > 255)
		return false;

	return KeyTimes[key.GetCode()] >= 0;
}

bool Keyboard::IsNewlyPressed (const Key &key)
{
	if (key.GetCode() < 0 || key.GetCode() > 255)
		return false;

	return KeyTimes[key.GetCode()] == 0;
}

bool Keyboard::IsRepeatedlyPressed (const Key &key)
{
	if (key.GetCode() < 0 || key.GetCode() > 255)
		return false;

	return KeyTimes[key.GetCode()] >= 0;
}

}}