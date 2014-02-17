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
	ContainerBase *Parent_;
	virtual void OSAttach(OSHandle handle) {}
	virtual void OSDetatch(OSHandle handle) {}
public:
	friend class ContainerBase;
	friend class Window;
	friend class ContainerWidget;

	LayoutRectangle Area;

	LayoutAble()
	: Parent_(nullptr){}
	virtual ~LayoutAble() {}

	virtual void Layout(Point pos, Size p) = 0;

	virtual void Parent(ContainerBase &container);
	virtual void UnParent();
	//void 
};

}}