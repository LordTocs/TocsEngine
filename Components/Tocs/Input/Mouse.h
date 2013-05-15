#pragma once
namespace Tocs {

namespace Graphics{ class SimpleWindow; }

namespace Input {
class Mouse
{
	
	void FetchPosition ();
	bool PrevLeftDown;
	bool LeftDown;
	bool RightDown;
	void SetInternalPosition (unsigned int x, unsigned int y);
	void SetLeftMouseState(bool state);
	bool Moved;
public:
	friend class ::Tocs::Graphics::SimpleWindow;

	unsigned int PrevX, PrevY;
	unsigned int X, Y;
	Mouse(void);

	void Hide ();
	void Show ();
	void Update ();

	void SetPosition (int X, int Y);

	bool IsLeftButtonDown () const { return LeftDown; }
	bool IsLeftButtonNewlyDown () const { return LeftDown && !PrevLeftDown; }

	int DeltaX () const { return X - PrevX; }
	int DeltaY () const { return Y - PrevY; }
};
}}

