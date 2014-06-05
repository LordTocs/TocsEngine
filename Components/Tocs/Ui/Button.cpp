#include "Button.h"
#include "NativeIncludes.h"
#include "App.h"

namespace Tocs {
namespace Ui {

static LRESULT CALLBACK ButtonProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Button *button = reinterpret_cast<Button *> (GetWindowLong(hwnd, GWL_USERDATA));

	return true;// button->InvokeParentProcedure(OSMessage(hwnd, msg, wParam, lParam));
}


Button::Button(const std::string &label)
	: Widget()
{
	Handle = CreateWindowEx(NULL,
		"BUTTON",
		label.c_str(),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10,
		10,
		10,
		10,
		App::GetDummyWindow(),
		(HMENU)GetUniqueID(),
		GetModuleHandle(NULL),
		NULL);

	//Determine minimums

	Area.Width.Min(80);
	Area.Height.Min(40);

	ConnectInternalHandle();

	std::cout << "Button Created: " << Handle << " : " << this << std::endl;
}

Button &Button::SetLabel(const std::string &label)
{
	SetWindowText(Handle, label.c_str());
	return *this;
}

std::string Button::GetLabel() const
{
	int txtlen = GetWindowTextLength(Handle);
	std::string s;  //or use wstring for wchar_t
	s.reserve(txtlen + 1);
	GetWindowText(Handle, const_cast<char*>(s.c_str()), txtlen);
	return s;
}

void Button::ProcessParentOSMessage(const OSMessage &message)
{
	if (message.Message == WM_COMMAND)
	{
		if (OnClick)
			OnClick();
	}
}

}}
