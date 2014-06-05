#include "Widget.h"
#include "NativeIncludes.h"
#include "App.h"
namespace Tocs {
namespace Ui {

unsigned int Widget::GetUniqueID() const
{
	static unsigned int id = 100;
	return id++;
}

Widget::Widget()
: Handle(nullptr) {}

Widget::~Widget()
{
	DestroyWindow(Handle);
}

void Widget::Show()
{
	ShowWindow(Handle, SW_SHOW);
}

void Widget::Hide()
{
	ShowWindow(Handle, SW_HIDE);
}

bool Widget::IsVisible() const
{
	return IsWindowVisible(Handle) != 0;
}

void Widget::Layout(Point pos, Size size)
{
	MoveWindow(Handle, pos.X, pos.Y, size.X, size.Y,true);
}

Size Widget::GetSize() const
{
	RECT rect;
	GetWindowRect(Handle, &rect);
	return Size(rect.right - rect.left, rect.bottom - rect.top);
}

Point Widget::GetPosition() const
{
	HWND parent = GetParent(Handle);
	POINT p;
	p.x = 0;
	p.y = 0;

	MapWindowPoints(Handle, parent, &p, 1);

	return Point(p.x, p.y);
}

void Widget::OSAttach(OSHandle handle)
{
	SetParent(Handle, handle);
}

void Widget::OSDetach(OSHandle /*handle*/)
{
	SetParent(Handle, App::GetDummyWindow());
}

void Widget::ConnectInternalHandle()
{
	SetWindowLong(Handle, GWL_USERDATA, reinterpret_cast<LONG> (this));
}

}}
