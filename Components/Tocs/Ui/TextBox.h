#pragma once
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
};

}}