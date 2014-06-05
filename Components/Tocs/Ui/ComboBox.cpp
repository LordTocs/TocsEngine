#include "ComboBox.h"
#include "NativeIncludes.h"
#include "App.h"
#include <CommCtrl.h>
#include <cassert>
namespace Tocs {
namespace Ui {

ComboBox::ComboBox()
{
	Handle = CreateWindowEx(0,
		WC_COMBOBOX,
		"",
		CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
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
	Area.Height.Pixels(28);

	ConnectInternalHandle();
}

void ComboBox::AddItem(const std::string &item)
{
	ComboBox_AddString(Handle, item.c_str());
	Items.emplace_back(std::make_unique<ListItem> (this, Items.size()));
}
bool ComboBox::HasSelection() const
{
	int sel = ComboBox_GetCurSel(Handle);
	return sel != CB_ERR;
}

ComboBox::ListItem &ComboBox::SelectedItem()
{
	int sel = ComboBox_GetCurSel(Handle);
	assert(sel != CB_ERR);
	return Item(sel);
}
const ComboBox::ListItem &ComboBox::SelectedItem() const
{
	int sel = ComboBox_GetCurSel(Handle);
	assert(sel != CB_ERR);
	return Item(sel);
}


void ComboBox::ProcessParentOSMessage(const OSMessage &message)
{
	if (message.Message == WM_COMMAND)
	{
		if (message.WParam.Hi == CBN_SELCHANGE)
		{
			if (OnSelectionChange) { OnSelectionChange(); }
		}
	}
}



///LIST ITEM

ComboBox::ListItem &ComboBox::ListItem::Text(const std::string &text)
{
	return *this;
}
std::string ComboBox::ListItem::Text() const
{
	unsigned int length = ComboBox_GetLBTextLen(Owner->Handle, Index);
	std::vector<char> buffer(length + 1);
	ComboBox_GetLBText(Owner->Handle,Index, &buffer[0]);
	return std::string(buffer.begin(), buffer.end());
}
void Remove()
{
}




}
}