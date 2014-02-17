#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include "VectorTypes.h"
namespace Tocs {
namespace Ui {

class LayoutHelper;
class LayoutAble;
class ContainerBase;
class LayoutContainer;

class LayoutRef
{
	LayoutAble *Reference;
public:
	LayoutRef(LayoutAble &ref) : Reference(&ref){}
	LayoutAble &Get() { return *Reference; }
	const LayoutAble &Get() const { return *Reference; }
};

class LayoutManager
{
	LayoutContainer *Owner;
	std::vector<std::unique_ptr<ContainerBase>> IntermediateContainers;
	ContainerBase *Root;
	void Layout(Point p, Size s);
public:
	friend class LayoutContainer;
	LayoutManager(LayoutContainer *owner);

	LayoutManager &operator()(LayoutHelper &helper);

	LayoutHelper &Vertical(std::initializer_list<LayoutRef> elements);
	LayoutHelper &Horizontal(std::initializer_list<LayoutRef> elements);
};

}}
