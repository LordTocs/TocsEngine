#pragma once
#include "VectorTypes.h"
#include "NativeHelpers.h"

#include "LayoutAble.h"
namespace Tocs {
namespace Ui {

class Widget : public LayoutAble
{
protected:
	OSHandle Handle;
	//Protected so the layout system can use it but the user can't
	//Virtual so container widgets can override.
	virtual void Layout(Point p, Size s);
	virtual void OSAttach(OSHandle handle);
	virtual void OSDetach(OSHandle handle);
	unsigned int GetUniqueID() const;

	void ConnectInternalHandle();
public:
	Widget();
	virtual ~Widget();

	void Show();
	void Hide();

	bool IsVisible() const;

	Size GetSize() const;
	Point GetPosition() const;

	const OSHandle &GetHandle() const { return Handle; }

	//Windows is stupid, and sometimes a message about a child widget goes to the parent.
	//This function lets the parent tell the child to process that message. Such as Buttons.
	virtual void ProcessParentOSMessage(const OSMessage &message) {}

	
};

}}