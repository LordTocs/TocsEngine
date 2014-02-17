#pragma once
#include <vector>
#include "VectorTypes.h"
namespace Tocs {
namespace Ui {

class LayoutAble;

class ContainerBase
{
	Point Position;
	Size RegionSize;
	unsigned int LastCount;
protected:
	void InternalAdd(LayoutAble &thing);
	void InternalRemove(LayoutAble &thing);
	
	std::vector<LayoutAble *> Items;

	virtual void DoLayout(Point p, Size s) = 0;
	
	
	virtual void EnforceMinimumSize(Size s) = 0;
public:

	friend class LayoutAble;

	virtual Size GetMinimumSize() const = 0;
	ContainerBase() : LastCount(0) {}
	virtual ~ContainerBase() {}

	virtual void OSDetach(LayoutAble &thing) = 0;
	virtual void OSAttach(LayoutAble &thing) = 0;

	void LayoutContents(Point p, Size s);

	void Add(LayoutAble &thing);
	void Remove(LayoutAble &thing);

	
};

}}