#pragma once
#ifdef WIN32
#include <Windows.h>
#endif
#include <string>
#include <Tocs/Graphics/ContextTarget.h>
#include "InputManager.h"
namespace Tocs {
namespace Input {

class SimpleWindow : public Graphics::ContextTarget
{
	////////////////////////////
	/////Windows Stuff//////////
	////////////////////////////
	#ifdef WIN32
	HWND WindowHandle;
	HINSTANCE WindowInstance;
	HDC hDC;
	HGLRC hRC;
	#endif

	int Width;
	int Height;
	bool Exiting;

	void SetLeftMouseState (bool state);
	void SetRightMouseState (bool state);
	void SetMousePosition (int x, int y);
	void SetMouseDelta (int dx, int dy);
	void SetKeyState (int key, bool state);
public:
	Tocs::Input::InputManager Input;

	SimpleWindow(std::string name, int width, int height, bool fullscreen, bool borderless);
	~SimpleWindow();

	void PumpMessages ();

	bool IsExiting () const { return Exiting; }

	void Show ();
	void Close ();

	HWND GetWindowHandle () { return WindowHandle; }
	HDC GetHDC () { return hDC; }
	void SetHGLRC (HGLRC hglrc) { hRC = hglrc; }
	HGLRC GetHGLRC () { return hRC; }

	int GetWidth () const { return Width; }
	int GetHeight () const { return Height; }
	int GetX () const;
	int GetY () const;

	friend LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

}}