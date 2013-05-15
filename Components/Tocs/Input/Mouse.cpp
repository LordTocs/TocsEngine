#include "Mouse.h"
#include <Windows.h>

namespace Tocs {
namespace Input {

Mouse::Mouse()
	: X(0), Y(0), PrevX(0), PrevY(0),PrevLeftDown(false), LeftDown(false), RightDown(false), Moved(false)
{
	//FetchPosition ();
}


void Mouse::FetchPosition ()
{
}

void Mouse::SetInternalPosition(unsigned int x, unsigned int y)
{
	PrevX = X;
	PrevY = Y;
	X = x;
	Y = y;
	Moved = true;
}

void Mouse::Update ()
{
	if (!Moved)
	{
		PrevX = X;
		PrevY = Y;
	}
	Moved = false;
}

void Mouse::Hide ()
{
	ShowCursor (false);
}

void Mouse::Show ()
{
	ShowCursor (true);
}

void Mouse::SetPosition (int x, int y)
{
	SetCursorPos (x,y);
}

void Mouse::SetLeftMouseState(bool state)
{
	PrevLeftDown = LeftDown;
	LeftDown = state;
}

}}