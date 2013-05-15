#pragma once
#ifdef WIN32
#include <Windows.h>
#endif
#include <string>
#include "ContextTarget.h"
#include <Tocs/Input/InputManager.h>
namespace Tocs {
namespace Graphics {

class SimpleWindow : public ContextTarget
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

	friend LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void SetLeftMouse (bool value) { Input.Mouse.SetLeftMouseState(value); }
	void SetMousePos (unsigned int x, unsigned int y) { Input.Mouse.SetInternalPosition(x,y); }
};

}}