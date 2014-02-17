#include "LayoutHelpers.h"
#include <algorithm>

namespace Tocs {
namespace Ui {

class LayoutHolder
{
public:
	int Pos;
	unsigned int Size;
	DimensionType Type;
	bool Maxed;
	int Index;
	LayoutHolder(int index) : Index(index), Pos(0), Size(0), Type(DimensionType::Strength), Maxed(false) {}
};

void LayoutHelper::OSDetach(LayoutAble &thing)
{
	if (Parent_ != nullptr)
	{
		Parent_->OSDetach(thing);
	}
	else
	{
		std::cout << "Attempted to detatch from null parent." << std::endl;
	}
}

void LayoutHelper::OSAttach(LayoutAble &thing)
{
	if (Parent_ != nullptr)
	{
		Parent_->OSAttach(thing);
	}
	else
	{
		std::cout << "Attempted to attach to null parent." << std::endl;
	}
}

void LayoutHelper::EnforceMinimumSize(Size s)
{
	Area.Width.Min(s.X);
	Area.Height.Min(s.Y);
}

void LayoutHelper::Layout(Point p, Size s)
{
	LayoutContents(p, s);
}


void LayoutHelper::RecursiveAttach(ContainerBase &base, LayoutAble &thing)
{
	base.OSAttach(thing);

	LayoutHelper *helper = dynamic_cast<LayoutHelper *> (&thing);
	if (helper != nullptr)
	{
		for (auto &i : helper->Items)
		{
			RecursiveAttach(base, *i);
		}
	}
}

void LayoutHelper::Parent(ContainerBase &container)
{
	if (Parent_ != nullptr)
	{
		for (auto &i : Items)
		{
			Parent_->OSDetach(*i);
		}
	}
	
	//Recursively OSAttach to the new container.
	for (auto &i : Items)
	{
		RecursiveAttach(container, *i);
	}

	LayoutAble::Parent(container); //Call base version
	
}
void LayoutHelper::RecursiveDetatch(ContainerBase &base, LayoutAble &thing)
{
	base.OSDetach(thing);

	LayoutHelper *helper = dynamic_cast<LayoutHelper *> (&thing);
	if (helper != nullptr)
	{
		for (auto &i : helper->Items)
		{
			RecursiveDetatch(base, *i);
		}
	}
}

void LayoutHelper::UnParent()
{
	if (Parent_ != nullptr)
	{
		for (auto &i : Items)
		{
			Parent_->OSDetach(*i);
		}
	}

	LayoutAble::UnParent(); //Call base version
}

///////////////////////////////////////////////////////////////

void HorizontalLayoutHelper::DoLayout(Point p, Size s)
{
	//Default layout along X axis.
	int nonspringwidth = s.X;
	std::vector<LayoutHolder> itemdata;
	int k = 0;
	for (auto &i : Items)
	{
		nonspringwidth -= i->Area.LeftMargin;
		nonspringwidth -= i->Area.RightMargin;
		if (i->Area.Width.Type() == DimensionType::Pixels)
		{
			nonspringwidth -= i->Area.Width.Pixels();
		}
		else
		{
			itemdata.push_back(LayoutHolder(k));
		}
		++k;
	}
	int workingwidth = nonspringwidth;

	//Jump to minimum width
	for (auto &item : itemdata)
	{
		LayoutAble *i = Items[item.Index];
		if (i->Area.Width.Min() != 0)
		{
			item.Size = i->Area.Width.Min();
			workingwidth -= item.Size;
		}
	}

	bool unchanged = false;
	while (workingwidth >= 0 && !unchanged)
	{
		unchanged = true;
		for (auto &item : itemdata)
		{
			if (workingwidth <= 0)
				break;
			LayoutAble *i = Items[item.Index];
			if (i->Area.Width.Max() == 0 || item.Size < i->Area.Width.Max())
			{
				unsigned int addition = i->Area.Width.Strength(); //Attempt to take our strength
				if (i->Area.Width.Max() > 0)
					addition = std::min(i->Area.Width.Max() - item.Size, addition); //Don't take more than we need
				addition = std::min(unsigned int(workingwidth), addition); //Don't take more than what's available

				item.Size += addition;
				if (addition != 0)
					unchanged = false;

				workingwidth -= addition;
			}
		}
	}
	unsigned int position = 0;
	int index = 0;
	//Actually layout items
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
			width = itemdata[index++].Size;
		}

		i->Layout(Point(position, i->Area.TopMargin) + p, Size(width, height));

		position += width + i->Area.RightMargin;
	}
}

Size HorizontalLayoutHelper::GetMinimumSize() const
{
	Size result;
	for (auto &i : Items)
	{
		result.X += i->Area.MinimumHorizontalSize();
		result.Y = std::max(result.Y, i->Area.MinimumVerticalSize());
	}
	return result;
}



/////////////////////////////////////////////////////////////////////////////////////////

void VerticalLayoutHelper::DoLayout(Point p, Size s)
{
	int nonspringheight = s.Y;
	std::vector<LayoutHolder> itemdata;
	int k = 0;
	for (auto &i : Items)
	{
		nonspringheight -= i->Area.TopMargin;
		nonspringheight -= i->Area.BottomMargin;
		if (i->Area.Height.Type() == DimensionType::Pixels)
		{
			nonspringheight -= i->Area.Height.Pixels();
		}
		else
		{
			itemdata.push_back(LayoutHolder(k));
		}
		++k;
	}
	int workingheight = nonspringheight;

	//Jump to minimum width
	for (auto &item : itemdata)
	{
		LayoutAble *i = Items[item.Index];
		if (i->Area.Height.Min() != 0)
		{
			item.Size = i->Area.Height.Min();
			workingheight -= item.Size;
		}
	}

	bool unchanged = false;
	while (workingheight >= 0 && !unchanged)
	{
		unchanged = true;
		for (auto &item : itemdata)
		{
			if (workingheight <= 0)
				break;
			LayoutAble *i = Items[item.Index];
			if (i->Area.Height.Max() == 0 || item.Size < i->Area.Height.Max())
			{
				unsigned int addition = i->Area.Height.Strength(); //Attempt to take our strength
				if (i->Area.Height.Max() > 0)
					addition = std::min(i->Area.Height.Max() - item.Size, addition); //Don't take more than we need
				addition = std::min(unsigned int(workingheight), addition); //Don't take more than what's available

				item.Size += addition;
				if (addition != 0)
					unchanged = false;

				workingheight -= addition;
			}
		}
	}

	unsigned int position = 0;
	int index = 0;
	//Actually layout items
	for (auto &i : Items)
	{
		position += i->Area.TopMargin;

		int width = s.X;
		width -= i->Area.HorizontalMargins();
		width = std::max(width, 0);
		if (i->Area.Width.Type() == DimensionType::Pixels)
		{
			width = i->Area.Width.Pixels();
		}
		else
		{
			if (i->Area.Width.Min() != 0)
				width = std::max(width, int(i->Area.Width.Min()));
			if (i->Area.Width.Max() != 0)
				width = std::min(width, int(i->Area.Width.Max()));
		}

		int height = 0;
		if (i->Area.Height.Type() == DimensionType::Pixels)
		{
			height = i->Area.Height.Pixels();
		}
		else
		{
			height = itemdata[index++].Size;
		}

		i->Layout(Point(i->Area.LeftMargin, position) + p, Size(width, height));

		position += height + i->Area.BottomMargin;
	}
}

Size VerticalLayoutHelper::GetMinimumSize() const
{
	Size result;
	for (auto &i : Items)
	{
		result.X = std::max(result.X, i->Area.MinimumHorizontalSize());
		result.Y += i->Area.MinimumVerticalSize();
	}
	return result;
}

}}