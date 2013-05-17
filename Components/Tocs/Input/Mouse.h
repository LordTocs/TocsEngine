#pragma once
namespace Tocs {

namespace Input {


class SimpleWindow;
class Mouse;

class MouseButton
{
	bool State; bool PrevState; bool Updated;

	void SetState (bool state);
public:
	friend Mouse;
	friend class SimpleWindow;
	MouseButton() : State(false), PrevState(false), Updated(false) {}

	bool IsDown () const { return State; }
	bool IsNewlyDown () const { return State && !PrevState; }
	bool IsUp () const { return !State; }
	bool IsNewlyUp () const { return !State && PrevState; }

	void Update ();
};

class Mouse
{
	bool Moved;
	SimpleWindow *Window;
	int Dx;
	int Dy;
	int XCoord;
	int YCoord;
public:
	MouseButton Left;
	MouseButton Right;

	friend class SimpleWindow;
	
	Mouse(SimpleWindow &window);

	void Hide ();
	void Show ();

	void SetPosition (int X, int Y);
	void SetScreenPosition (int X, int Y);

	const int &X () const { return XCoord; }
	const int &Y () const { return YCoord; }
	const int &DeltaX () const { return Dx; }
	const int &DeltaY () const { return Dy; }

	void Update ();
};

}}

