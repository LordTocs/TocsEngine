#pragma once
#include <functional>
#include "Widget.h"

namespace Tocs {
namespace Ui {

class ComboBox : public Widget
{
public:
	class Item
	{
		ComboBox *Owner;
		unsigned int index;
	public:
		Item(ComboBox *box, unsigned int index)
		: Owner(box) {}

		Item &Text(const std::string &text);
		std::string Text() const;


	};
	friend class Item;

	ComboBox();

	void AddItem(const std::string &item);

	unsigned int ItemCount() const;

};

}}