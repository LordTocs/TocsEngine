#include "ContainerBase.h"
#include "LayoutAble.h"
#include <algorithm>
namespace Tocs {
namespace Ui {

void ContainerBase::Add(LayoutAble &thing)
{
	if (thing.Parent != nullptr)
		thing.Parent->Remove(thing);

	thing.Parent = this;
	OSAttach(thing);
	Items.push_back(&thing);

	Layout(Position, RegionSize);
}

void ContainerBase::Remove(LayoutAble &thing)
{
	auto i = std::find(Items.begin(), Items.end(), &thing);
	if (i == Items.end())
		return;

	OSDetach(thing);
	thing.Parent = nullptr;
	Items.erase(i);
}

void ContainerBase::Layout(Point p, Size s)
{
	if (p.X == Position.X && p.Y == Position.Y && s.X == RegionSize.X && s.Y == RegionSize.Y && LastCount == Items.size())
		return; //No change
	Position = p;
	RegionSize = s;
	LastCount = Items.size();
	DoLayout(p, s);
}

void ContainerBase::DoLayout(Point p, Size s)
{
	//Default layout along X axis.
	int workingwidth = s.X;
	float totalspring = 0;
	for (auto &i : Items)
	{
		workingwidth -= i->Area.LeftMargin;
		workingwidth -= i->Area.RightMargin;
		if (i->Area.Width.Type() == DimensionType::Pixels)
		{
			workingwidth -= i->Area.Width.Pixels();
		}
		else
		{
			totalspring += i->Area.Width.Strength();
		}
	}

	unsigned int position = 0;

	for (auto &i : Items)
	{
		position += i->Area.LeftMargin;

		int height = s.Y;
		height -= i->Area.TopMargin + i->Area.BottomMargin;
		height = std::max(height, 0);
		if (i->Area.Height.Type() == DimensionType::Pixels)
		{
			height = i->Area.Height.Pixels();
		}
		else
		{
			if (i->Area.Height.Min() != 0)
				height = std::max(height, int(i->Area.Height.Min()));
			if (i->Area.Height.Max() != 0)
				height = std::min(height, int(i->Area.Height.Max()));
		}
		
		int width = 0;
		if (i->Area.Width.Type() == DimensionType::Pixels)
		{
			width = i->Area.Width.Pixels();
		}
		else
		{
			width = int (workingwidth * (i->Area.Width.Strength() / totalspring));
		}

		i->Layout(Point(position, i->Area.TopMargin), Size(width,height));

		position += width + i->Area.RightMargin;
	}
}

}}