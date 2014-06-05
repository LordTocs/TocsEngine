#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "Widget.h"

namespace Tocs {
namespace Ui {

class ComboBox : public Widget
{
public:
	class ListItem
	{
		ComboBox *Owner;
		unsigned int Index;
	public:
		ListItem(ComboBox *box, unsigned int index)
		: Owner(box), Index(index) {}

		ListItem &Text(const std::string &text);
		std::string Text() const;

		void Remove();
	};
	friend class Item;
protected:
	//Maintain a list of items so pointers to items work correctly. 
	//Kind of a lame solution because of extra memory, but it works correctly
	std::vector<std::unique_ptr<ListItem>> Items;
public:
	ComboBox();
	ComboBox(const ComboBox &) = delete;
	ComboBox &operator=(const ComboBox &) = delete;

	void AddItem(const std::string &item);
	
	ListItem &Item(unsigned int index) { return *Items[index]; }
	const ListItem &Item(unsigned int index) const { return *Items[index]; }

	bool HasSelection() const;
	ListItem &SelectedItem();
	const ListItem &SelectedItem() const;
	std::function<void()> OnSelectionChange;

	unsigned int ItemCount() const { return Items.size(); }

	virtual void ProcessParentOSMessage(const OSMessage &message);

};

}}