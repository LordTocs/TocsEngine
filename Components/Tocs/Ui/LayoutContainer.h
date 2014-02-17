#pragma once
#include "ContainerBase.h"
#include "LayoutManager.h"
namespace Tocs {
namespace Ui {

class LayoutContainer : public ContainerBase
{
protected:
	virtual void OSDetach(LayoutAble &thing) = 0;
	virtual void OSAttach(LayoutAble &thing) = 0;
	void DoLayout(Point p, Size s);
	virtual Size GetMinimumSize() const;
public:
	LayoutManager Layout;
	LayoutContainer() : Layout(this){}

	LayoutContainer(const LayoutContainer &) = delete;
	
};


}}