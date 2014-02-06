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

class LayoutHolder
{
public:
	int Pos;
	unsigned int Width;
	DimensionType Type;
	LayoutHolder() : Pos(0), Width(0), Type(DimensionType::Strength) {}
};


void ContainerBase::DoLayout(Point p, Size s)
{
	//Default layout along X axis.
	int workingwidth = s.X;
	float totalspring = 0;
	std::vector<LayoutHolder> itemdata;
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
			itemdata.push_back(LayoutHolder());
		}
	}

	unsigned int position = 0;
	int index = 0;
	
	for (int i = 0; i < Items.size(); ++i)
	{
		LayoutAble *item = Items[i];
		position += item->Area.LeftMargin;

		if (item->Area.Width.Type() == DimensionType::Pixels)
		{
			position += item->Area.Width.Pixels() + item->Area.RightMargin;
			continue;
		}

		itemdata[index].Pos = position;
		if (itemdata[index].Type == DimensionType::Strength)
		{
			itemdata[index].Width = int(workingwidth * (item->Area.Width.Strength() / totalspring));
			if (item->Area.Width.Min() != 0 && itemdata[index].Width < item->Area.Width.Min())
			{
				itemdata[index].Width = item->Area.Width.Min();
				itemdata[index].Type == DimensionType::Pixels;
				totalspring -= item->Area.Width.Strength();
				workingwidth -= itemdata[index].Width;
				//Reset and relayout.
				index = 0;
				position = 0;
				i = 0;
			}
			else if (item->Area.Width.Max() != 0 && itemdata[index].Width > item->Area.Width.Max())
			{
				itemdata[index].Width = item->Area.Width.Max();
				itemdata[index].Type == DimensionType::Pixels;
				totalspring -= item->Area.Width.Strength();
				workingwidth -= itemdata[index].Width;
				//Reset and relayout.
				index = 0;
				position = 0;
				i = 0;
			}
		}
		else
		{
			position += itemdata[index].Width = item->Area.Width.Max();
		}
		position += item->Area.RightMargin;
		index++;
	}


	index = 0;

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
			width = itemdata[index++].Width;
		}

		i->Layout(Point(position, i->Area.TopMargin), Size(width,height));

		position += width + i->Area.RightMargin;
	}

	EnforceMinimumSize(GetMinimumSize());
}


Size ContainerBase::GetMinimumSize() const
{
	Size result;
	for (auto &i : Items)
	{
		result.X += i->Area.MinimumHorizontalSize();
		result.Y = std::max(result.Y, i->Area.MinimumVerticalSize());
	}
	return result;
}

}}