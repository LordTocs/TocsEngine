#include "Mouse.h"
#include "SimpleWindow.h"
#include <Windows.h>

namespace Tocs {
namespace Input {

Mouse::Mouse(SimpleWindow &window)
	: XCoord(0), YCoord(0), Dx(0), Dy(0), Window(&window)
{}

void MouseButton::SetState (bool state)
{
	PrevState = State;
	State = state;
	Updated = true;
}

void MouseButton::Update()
{
	if (!Updated)
	{
		PrevState = State;
	}
	Updated = false;
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
	x += Window->GetX();
	y += Window->GetY();
	SetCursorPos (x, y);
}

void Mouse::SetScreenPosition (int X, int Y)
{
	SetCursorPos(X,Y);
}

void Mouse::Update()
{
	Left.Update();
	Right.Update();

	if (!Moved)
	{
		Dx = 0;
		Dy = 0;
	}
	Moved = false;
}


}}