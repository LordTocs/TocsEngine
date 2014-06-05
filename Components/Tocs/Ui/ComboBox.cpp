#include "ComboBox.h"
#include "NativeIncludes.h"
#include "App.h"
namespace Tocs {
namespace Ui {

ComboBox::ComboBox()
{
	Handle = CreateWindowEx(WC_COMBOBOX,
		"",
		"",
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
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

	ConnectInternalHandle();
}

}
}