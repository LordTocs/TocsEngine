#pragma once

namespace Tocs {
namespace Ui {

class DimensionType
{
	enum InternalFormat
	{
		pixels,
		strength
	};
	DimensionType(InternalFormat format) : Internal(format) {}

	InternalFormat Internal;
public:
	const static DimensionType Pixels;
	const static DimensionType Strength;

	bool operator ==  (const DimensionType &op2) const { return Internal == op2.Internal; }
	bool operator !=  (const DimensionType &op2) const { return Internal != op2.Internal; }
};

class SpringDimension
{
	union DimValue
	{
		float StrengthValue;
		unsigned int PixelValue;
		DimValue(float s) : StrengthValue(s) {}
		DimValue(unsigned int p) : PixelValue(p) {}
	};
	DimValue Value;
	DimensionType Type_;
	unsigned int MinPixels;
	unsigned int MaxPixels;
public:
	SpringDimension();

	SpringDimension &Pixels(unsigned int pixels)
	{ Value.PixelValue = pixels; Type_ = DimensionType::Pixels;  return *this; }

	unsigned int Pixels() const
	{ return Value.PixelValue; }


	SpringDimension &Strength(float strength)
	{ Value.StrengthValue = strength; Type_ = DimensionType::Strength; return *this; }

	float Strength() const
	{ return Value.StrengthValue; }

	unsigned int Min() const
	{ return MinPixels; }

	SpringDimension &Min(unsigned int pixels)
	{ MinPixels = pixels; return *this; }

	unsigned int Max() const
	{ return MaxPixels;	}

	SpringDimension &Max(unsigned int pixels)
	{ MaxPixels = pixels; return *this;	}

	DimensionType Type() const { return Type_; }
};

class LayoutRectangle
{
public:
	SpringDimension Width;
	SpringDimension Height;
	unsigned int TopMargin;
	unsigned int BottomMargin;
	unsigned int LeftMargin;
	unsigned int RightMargin;

	LayoutRectangle &Margin(unsigned int value);
	LayoutRectangle &Margin(unsigned int h, unsigned int v);
	LayoutRectangle &Margin(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right);

	unsigned int VerticalMargins() const { return TopMargin + BottomMargin; }
	unsigned int HorizontalMargins() const { return LeftMargin + RightMargin; }

	unsigned int MinimumVerticalSize() const { return VerticalMargins() + Height.Min(); }
	unsigned int MinimumHorizontalSize() const { return HorizontalMargins() + Width.Min(); }
};

}}