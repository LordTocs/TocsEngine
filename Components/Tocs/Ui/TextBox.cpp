#include "TextBox.h"
#include "NativeIncludes.h"
#include "App.h"
#include <vector>
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

	ConnectInternalHandle();
}

std::string TextBox::Text() const
{
	unsigned int length = Edit_GetTextLength(Handle);
	std::vector<char> buffer(length + 1);
	Edit_GetText(Handle, &buffer[0], length + 1);
	return std::string(buffer.begin(), buffer.end());
}

TextBox &TextBox::Text(const std::string &text)
{
	Edit_SetText(Handle, text.c_str());
	return *this;
}

TextBox &TextBox::MaxLength(unsigned int length)
{
	Edit_LimitText(Handle, length);
	return *this;
}

void TextBox::ProcessParentOSMessage(const OSMessage &message)
{
	if (message.Message == WM_COMMAND)
	{
		if (message.WParam.Hi == EN_CHANGE)
		{
			if (TextChanged)
			{
				TextChanged();
			}
		}
	}
}


}}