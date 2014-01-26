#pragma once
#include <vector>
#include "VectorTypes.h"
namespace Tocs {
namespace Ui {

class LayoutAble;

class ContainerBase
{
	std::vector<LayoutAble *> Items;
	Point Position;
	Size RegionSize;
	unsigned int LastCount;
protected:
	virtual void OSDetach(LayoutAble &thing) = 0;
	virtual void OSAttach(LayoutAble &thing) = 0;
	virtual void DoLayout(Point p, Size s);
	void Layout(Point p, Size s);
public:
	ContainerBase() : LastCount(0) {}
	virtual ~ContainerBase() {}

	void Add(LayoutAble &thing);
	void Remove(LayoutAble &thing);

	
};

}}