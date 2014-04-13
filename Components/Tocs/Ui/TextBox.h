#pragma once
#include <functional>
#include "Widget.h"

namespace Tocs {
namespace Ui {

class TextBox : public Widget
{
public:
	TextBox();
	~TextBox() {}

	TextBox(const TextBox &) = delete;
	TextBox &operator= (const TextBox&) = delete;

	std::function <void()> TextChanged;
	std::function <void()> CursorChanged;
};

}}