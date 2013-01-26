#pragma once
namespace Tocs {

namespace Graphics{ class SimpleWindow; }

namespace Input {
class Mouse
{
	
	void FetchPosition ();
	bool LeftDown;
	bool RightDown;
	void SetPosition (unsigned int x, unsigned int y);
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
};
}}

