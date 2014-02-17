#pragma once
#include "ContainerBase.h"
#include "LayoutAble.h"
namespace Tocs {
namespace Ui {

class LayoutHelper : public ContainerBase, public LayoutAble
{
	static void RecursiveAttach(ContainerBase &base, LayoutAble &thing);
	static void RecursiveDetatch(ContainerBase &base, LayoutAble &thing);
protected:
	void EnforceMinimumSize(Size s);
public:
	

	void OSDetach(LayoutAble &thing);
	void OSAttach(LayoutAble &thing);

	void Layout(Point p, Size s);

	void Parent(ContainerBase &container);
	void UnParent();
};

class HorizontalLayoutHelper : public LayoutHelper
{
protected:
	void DoLayout(Point p, Size s);
	Size GetMinimumSize() const;
public:
};

class VerticalLayoutHelper : public LayoutHelper
{
protected:
	void DoLayout(Point p, Size s);
	Size GetMinimumSize() const;
public:
};


}}