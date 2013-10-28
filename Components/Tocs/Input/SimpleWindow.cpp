#include "SimpleWindow.h"
#define NOMINMAX
#include <Windows.h>
#include <WindowsX.h>
namespace Tocs {
namespace Input {


LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SimpleWindow *windowinst = reinterpret_cast<SimpleWindow *> (GetWindowLong (hWnd, GWL_USERDATA));

	switch(message)
	{  // A key has been pressed, end the app
		case WM_CLOSE:    //User hit the Close Window button, end the app
			windowinst->Exiting = true;
			return 0;
		case WM_LBUTTONDOWN:
			windowinst->SetLeftMouseState(true);
			windowinst->SetMousePosition(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
			break;
		case WM_LBUTTONUP:
			windowinst->SetLeftMouseState(false);
			windowinst->SetMousePosition(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
			break;
		case WM_MOUSEMOVE:
			windowinst->SetMousePosition(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
			break;
		case WM_INPUT:
		{
			RAWINPUT inputbuffer;
			unsigned int buffsize = sizeof(RAWINPUT);
			GetRawInputData(reinterpret_cast<HRAWINPUT> (lParam),RID_INPUT,&inputbuffer,&buffsize,sizeof(RAWINPUTHEADER));
				  
			switch (inputbuffer.header.dwType)
			{
				case RIM_TYPEMOUSE:
					if (inputbuffer.data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
						windowinst->SetMouseDelta(inputbuffer.data.mouse.lLastX,inputbuffer.data.mouse.lLastY);
					break;
				case RIM_TYPEKEYBOARD:
					windowinst->SetKeyState(inputbuffer.data.keyboard.VKey,!(inputbuffer.data.keyboard.Flags & RI_KEY_BREAK));
					break;
			}
		}
		break;
	}
   
    return (DefWindowProc(hWnd,message,wParam,lParam));

}

SimpleWindow::SimpleWindow(std::string title, int width, int height, bool fullscreen, bool borderless)
	: Width (width), Height(height),Exiting(false),Input(*this)
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

	RAWINPUTDEVICE raw_input_devices[2];
 
  // Keyboard:
  raw_input_devices[0].usUsagePage = 0x01;
  raw_input_devices[0].usUsage = 0x06;
  raw_input_devices[0].hwndTarget = NULL;
  raw_input_devices[0].dwFlags = 0;
 
  // Mouse:
  raw_input_devices[1].usUsagePage = 0x01;
  raw_input_devices[1].usUsage = 0x02;
  raw_input_devices[1].hwndTarget = NULL;
  raw_input_devices[1].dwFlags = 0;
 

  RegisterRawInputDevices(&raw_input_devices[0],2,sizeof(RAWINPUTDEVICE));
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

int SimpleWindow::GetX () const
{
	RECT rect;
	GetWindowRect (WindowHandle,&rect);
	return rect.left;
}

int SimpleWindow::GetY () const
{
	RECT rect;
	GetWindowRect (WindowHandle,&rect);
	return rect.top;
}

void SimpleWindow::SetLeftMouseState (bool state) 
{
	Input.Mouse.Left.SetState(state);
}
void SimpleWindow::SetRightMouseState (bool state) 
{
	Input.Mouse.Right.SetState(state);
}
void SimpleWindow::SetMousePosition (int x, int y) 
{
	Input.Mouse.XCoord = x;
	Input.Mouse.YCoord = y;
}
void SimpleWindow::SetMouseDelta (int dx, int dy) 
{
	Input.Mouse.Dx = dx;
	Input.Mouse.Dy = dy;
	Input.Mouse.Moved = true;
}

void SimpleWindow::SetKeyState (int key, bool state)
{
	if (state)
	{
		if (Input.Keyboard.KeyTimes[key] < 0)
			Input.Keyboard.KeyTimes[key] = 0;
	}
	else
	{
		Input.Keyboard.KeyTimes[key] = -1;
	}
}


}}