#pragma once
#include <string>
#include <functional>
#include "Widget.h"

namespace Tocs {
namespace Ui {

class Button : public Widget
{
public:
	Button(const std::string &label);
	~Button() {}

	Button(const Button &) = delete;
	Button &operator= (const Button&) = delete;

	Button &SetLabel(const std::string &label);
	std::string GetLabel() const;

	std::function <void()> OnClick;

	virtual void ProcessParentOSMessage(const OSMessage &message);
};

}}