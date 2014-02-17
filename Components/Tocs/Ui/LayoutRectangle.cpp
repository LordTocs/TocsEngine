#include "LayoutRectangle.h"

namespace Tocs {
namespace Ui {


const DimensionType DimensionType::Pixels(pixels);
const DimensionType DimensionType::Strength(strength);

SpringDimension::SpringDimension()
	: Value(1),
	Type_(DimensionType::Strength),
	MinPixels(0),
	MaxPixels(0)
{
}

LayoutRectangle::LayoutRectangle()
: TopMargin(3), BottomMargin(3), LeftMargin(3), RightMargin(3)
{

}

LayoutRectangle &LayoutRectangle::Margin(unsigned int value)
{
	TopMargin = value;
	BottomMargin = value;
	LeftMargin = value;
	RightMargin = value;
	return *this;
}

LayoutRectangle &LayoutRectangle::Margin(unsigned int h, unsigned int v)
{
	TopMargin = v;
	BottomMargin = v;
	LeftMargin = h;
	RightMargin = h;
	return *this;
}
LayoutRectangle &LayoutRectangle::Margin(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right)
{
	TopMargin = top;
	BottomMargin = bottom;
	LeftMargin = left;
	RightMargin = right;
	return *this;
}


}}