#include "TextBox.h"
#include "NativeIncludes.h"
#include "App.h"
namespace Tocs {
namespace Ui {

TextBox::TextBox()
{
	Handle = CreateWindowEx(WS_EX_CLIENTEDGE,
		"EDIT",
		"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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
	Area.Height.Pixels(23);

	SetWindowLong(Handle, GWL_USERDATA, reinterpret_cast<LONG> (this));

	std::cout << "Textbox Created: " << Handle << " : " << this << std::endl;
}

}}