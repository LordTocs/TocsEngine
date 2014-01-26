#pragma once
#include "NativeHelpers.h"
#include "VectorTypes.h"
#include "LayoutRectangle.h"

namespace Tocs {
namespace Ui {

class ContainerBase;

class LayoutAble
{
protected:
	ContainerBase *Parent;

	virtual void Layout(Point pos, Size p) = 0;
	virtual void OSAttach(OSHandle handle) {}
	virtual void OSDetatch(OSHandle handle) {}
public:
	friend class ContainerBase;
	friend class Window;
	friend class ContainerWidget;

	LayoutRectangle Area;

	LayoutAble()
	: Parent(nullptr){}
	virtual ~LayoutAble() {}
};

}}