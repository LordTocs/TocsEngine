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

	std::string Text() const;
	TextBox &Text(const std::string &text);

	TextBox &MaxLength(unsigned int length);

	std::function <void()> TextChanged;
	std::function <void()> CursorChanged;
	

	virtual void ProcessParentOSMessage(const OSMessage &message);


};

}}