#include "ContainerBase.h"
#include "LayoutAble.h"
#include <algorithm>
namespace Tocs {
namespace Ui {

void ContainerBase::Add(LayoutAble &thing)
{
	if (thing.Parent_ != nullptr)
		thing.UnParent();

	thing.Parent(*this);
}

void ContainerBase::InternalAdd(LayoutAble &thing)
{
	OSAttach(thing);
	Items.push_back(&thing);
	LayoutContents(Position, RegionSize);
}

void ContainerBase::Remove(LayoutAble &thing)
{
	if (thing.Parent_ != this)
		return;

	thing.UnParent();
}

void ContainerBase::InternalRemove(LayoutAble &thing)
{
	auto i = std::find(Items.begin(), Items.end(), &thing);
	if (i == Items.end())
		return;

	OSDetach(thing);

	Items.erase(i);
}

void ContainerBase::LayoutContents(Point p, Size s)
{
	if (p.X == Position.X && p.Y == Position.Y && s.X == RegionSize.X && s.Y == RegionSize.Y && LastCount == Items.size())
		return; //No change
	Position = p;
	RegionSize = s;
	LastCount = Items.size();
	DoLayout(p, s);
	EnforceMinimumSize(GetMinimumSize());
}

class LayoutHolder
{
public:
	int Pos;
	unsigned int Width;
	DimensionType Type;
	bool Maxed;
	int Index;
	LayoutHolder(int index) : Index(index), Pos(0), Width(0), Type(DimensionType::Strength), Maxed(false) {}
};


}}