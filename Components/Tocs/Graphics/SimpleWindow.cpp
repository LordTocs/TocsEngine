#include "SimpleWindow.h"
#include <Windows.h>
#include <WindowsX.h>
namespace Tocs {
namespace Graphics {


LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SimpleWindow *windowinst = reinterpret_cast<SimpleWindow *> (GetWindowLong (hWnd, GWL_USERDATA));

	switch(message)
	{  // A key has been pressed, end the app
      case WM_CLOSE:    //User hit the Close Window button, end the app
		  windowinst->Exiting = true;
		  return 0;
	  case WM_LBUTTONDOWN:
		  windowinst->SetLeftMouse(true);
		  break;
	  case WM_LBUTTONUP:
		  windowinst->SetLeftMouse(false);
		  break;
	  case WM_MOUSEMOVE:
		  windowinst->SetMousePos(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		  break;
    }
   
    return (DefWindowProc(hWnd,message,wParam,lParam));

}

SimpleWindow::SimpleWindow(std::string title, int width, int height, bool fullscreen, bool borderless)
	: Width (width), Height(height),Exiting(false)
{
	WNDCLASS window_class;
	WindowInstance = GetModuleHandle (NULL);
	window_class.style          = CS_OWNDC;
	window_class.cbClsExtra     = 0;
	window_class.cbWndExtra     = 0;
	window_class.hInstance      = WindowInstance;
	window_class.hIcon          = LoadIcon(NULL,IDI_APPLICATION);
	window_class.hCursor        = LoadCursor(NULL,IDC_ARROW);
	window_class.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
	window_class.lpszMenuName   = NULL;
	window_class.lpszClassName  = "Game Window";
	window_class.lpfnWndProc    = WndProc;

	if (!RegisterClass (&window_class))
	{
		//crap...
		return;
	}
	DWORD style;
	if (fullscreen)
	{
		Width = GetSystemMetrics(SM_CXSCREEN);
		Height = GetSystemMetrics(SM_CYSCREEN);
		style = WS_POPUP|WS_VISIBLE;
	}
	else
	{
		Width = width;
		Height = height;
		style = WS_OVERLAPPED|WS_SYSMENU|WS_VISIBLE;
	}
	WindowHandle = CreateWindow ("Game Window",title.c_str (),style,0,0,Width,Height,NULL,NULL,WindowInstance,NULL);

	if (!WindowHandle)
	{
		//crap...again...
		return;

	}

	if (!fullscreen)
	{
		RECT rect;
		GetClientRect (WindowHandle,&rect);
		int FrameWidth = Width + (Width - rect.right);
		int FrameHeight = Height + (Height - rect.bottom);
		MoveWindow (WindowHandle, 0, 0, FrameWidth, FrameHeight, TRUE);
	}

	if (!(hDC = GetDC (WindowHandle)))
	{
		//ERRORORROROROROR
	}

	SetWindowLong (WindowHandle, GWL_USERDATA, reinterpret_cast<LONG> (this));
}


SimpleWindow::~SimpleWindow(void)
{
	DestroyWindow (WindowHandle);

}

void SimpleWindow::PumpMessages ()
{
#ifdef WIN32
	MSG msg;
	while (PeekMessage (&msg,NULL, 0,0, PM_REMOVE))
	{
		TranslateMessage (&msg);
		DispatchMessage(&msg);
	}
#endif
}

void SimpleWindow::Show ()
{
	ShowWindow (WindowHandle, SW_SHOW);
}

void SimpleWindow::Close ()
{
	DestroyWindow (WindowHandle);
}

}}