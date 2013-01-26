#include "Mouse.h"
#include <Windows.h>

namespace Tocs {
namespace Input {

Mouse::Mouse()
	: X(0), Y(0), PrevX(0), PrevY(0), LeftDown(false), RightDown(false)
{
	FetchPosition ();
}


void Mouse::FetchPosition ()
{
	/*POINT cursor;
	GetCursorPos (&cursor);
	X = cursor.x;
	Y = cursor.y;*/
}

void Mouse::SetPosition(unsigned int x, unsigned int y)
{
	PrevX = X;
	PrevY = Y;
	X = x;
	Y = y;
}

void Mouse::Update ()
{
	PrevX = X;
	PrevY = Y;
	FetchPosition ();
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

}}