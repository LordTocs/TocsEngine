#include "Window.h"
#include "NativeIncludes.h"
#include <algorithm>
#include <Tocs/Core/StaticInitializer.h>

#include "Widget.h"


//Makes sure that the app doesn't look like windows 3.1, Not sure how but it does.
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;

namespace Tocs {
namespace Ui {

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	OSMessage message(hwnd, msg, wParam, lParam);
	Window *windowinst = reinterpret_cast<Window *> (GetWindowLong(hwnd, GWL_USERDATA));
	switch (msg)
	{
	case WM_CLOSE:
	{
		if (windowinst->OnClose)
			windowinst->OnClose();
		DestroyWindow(hwnd);

	}
		break;
	case WM_SIZE:
	{
		if (wParam == SIZE_MAXIMIZED)
		{
			if (windowinst->OnMaximize)
				windowinst->OnMaximize();
		}
		else if (wParam == SIZE_MINIMIZED)
		{
			if (windowinst->OnMinimize)
				windowinst->OnMinimize();
		}
		else if (wParam == SIZE_RESTORED)
		{
			if (windowinst->OnResize)
				windowinst->OnResize(LOWORD(lParam), HIWORD(lParam));
		}
		windowinst->LayoutContents(Point(0, 0), Size(LOWORD(lParam), HIWORD(lParam)));
	}
		break;
	case WM_MOVE:
	{
		if (windowinst->OnMove)
			windowinst->OnMove(LOWORD(lParam), HIWORD(lParam));
	}
		break;
	case WM_COMMAND:
	{
		unsigned int id = LOWORD(wParam);
		HWND widgethandle = GetDlgItem(hwnd, id);

		if (!widgethandle)
			break;

		Widget *widget = reinterpret_cast<Widget *> (GetWindowLong(widgethandle, GWL_USERDATA));

		if (widget != nullptr)
		{
			widget->ProcessParentOSMessage(message);
		}

	}
		break;
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* mmi = (MINMAXINFO *)lParam;
		mmi->ptMinTrackSize.x = windowinst->MinSize_.X;
		mmi->ptMinTrackSize.y = windowinst->MinSize_.Y;
	}
		break;
	default:
		return (DefWindowProc(hwnd, msg, wParam, lParam));
	}

	return 0;
}


static WNDCLASSEX WindowClass;
static void InitWindowClass()
{
	HINSTANCE Instance(GetModuleHandle(nullptr));
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = Instance;
	WindowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = nullptr;
	WindowClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	WindowClass.lpszClassName = "TocsWindow";

	if (!RegisterClassEx(&WindowClass))
	{
		//WTF happened here.
		cout << "Error registering class TocsWindow" << endl;
		return;
	}
}
static StaticInitializer init(&InitWindowClass);



Window::Window(const std::string &title, Size size)
	: Handle(nullptr)
{
	Handle = CreateWindowEx(WS_EX_CLIENTEDGE, "TocsWindow", title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.X, size.Y, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

	if (Handle == nullptr)
	{
		cout << "Error creating window" << endl;
	}

	SetWindowLong(Handle, GWL_USERDATA, reinterpret_cast<LONG> (this));
}


Window::~Window(void)
{
	Close();
}

void Window::Close()
{
	CloseWindow(Handle);
}

Window &Window::Hide()
{
	ShowWindow(Handle, SW_HIDE); return *this;
}

Window &Window::Show()
{
	ShowWindow(Handle, SW_SHOW); return *this;
}

Window &Window::Maximize()
{
	ShowWindow(Handle, SW_MAXIMIZE); return *this;
}

Window &Window::Minimize()
{
	ShowWindow(Handle, SW_MINIMIZE); return *this;
}

Window &Window::SetPosition(unsigned int x, unsigned int y)
{
	auto size = GetWindowSize();
	MoveWindow(Handle, x, y, size.X, size.Y, false);
	return *this;
}
Point Window::GetPosition() const
{
	RECT rect;
	GetWindowRect(Handle, &rect);
	return Point(rect.left, rect.top);
}

Size Window::GetClientSize() const
{
	RECT rect;
	GetClientRect(Handle, &rect);
	return Size(rect.right, rect.bottom);
}
Size Window::GetWindowSize() const
{
	RECT rect;
	GetWindowRect(Handle, &rect);
	return Size(rect.right - rect.left, rect.bottom - rect.top);
}
Window &Window::SetClientSize(unsigned int w, unsigned int h)
{
	auto pos = GetPosition();
	MoveWindow(Handle, pos.X, pos.Y, w, h, false);
	auto intermediatesize = GetClientSize();
	unsigned int adjustx = w - intermediatesize.X;
	unsigned int adjusty = h - intermediatesize.Y;
	MoveWindow(Handle, pos.X, pos.Y, w + adjustx, h + adjusty, false);
	return *this;
}
Window &Window::SetClientSize(const Size &size)
{
	SetClientSize(size.X, size.Y);
	return *this;
}
Window &Window::SetWindowSize(unsigned int w, unsigned int h)
{
	auto pos = GetPosition();
	MoveWindow(Handle, pos.X, pos.Y, w, h, false);
	return *this;
}
Window &Window::SetWindowSize(const Size &size)
{
	SetWindowSize(size.X, size.Y);
	return *this;
}

Window &Window::MinSize(Size size)
{
	RECT winsize;
	GetWindowRect(Handle, &winsize);
	Size client = GetClientSize();
	Size framesize((winsize.right - winsize.left) - client.X, (winsize.bottom - winsize.top) - client.Y);
	MinSize_ = size + framesize;

	bool resize = false;
	if (client.X < size.X)
	{
		client.X = std::max(client.X, size.X);
		resize = true;
	}
	if (client.Y < size.Y)
	{
		client.Y = std::max(client.Y, size.Y);
		resize = true;
	}
	if (resize)
		this->SetClientSize(client);

	return *this;
}

void Window::OSAttach(LayoutAble &thing)
{
	thing.OSAttach(Handle);
}

void Window::OSDetach(LayoutAble &thing)
{
	thing.OSDetatch(Handle);
}

void Window::EnforceMinimumSize(Size size)
{
	MinSize(size);
}

}}