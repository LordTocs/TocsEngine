#pragma once
struct HWND__;
typedef HWND__ *HWND;
typedef HWND OSHandle;

struct HINSTANCE__;
typedef HINSTANCE__ *HINSTANCE;

typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef long LRESULT;

//LRESULT CALLBACK WindowProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
typedef LRESULT(__stdcall *WNDPROC) (HWND, UINT, WPARAM, LPARAM);
typedef WNDPROC WindowProcedure; //LRESULT (__stdcall *WindowProcedure) (HWND, UINT, WPARAM, LPARAM);

class OSMessage
{
public:
	HWND Handle;
	UINT Message;
	WPARAM WParam;
	LPARAM LongParam;

	OSMessage(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
		: Handle(handle), Message(msg), WParam(wparam), LongParam(lparam) {}
};
