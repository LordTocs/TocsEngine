#pragma once
#include <string>


namespace Tocs {
namespace Graphics {

class TextureFormat
{
	enum InternalFormat
	{
		rgb4,
		rgb5,
		rgb8,
		rgb10,
		rgb12,
		rgb16,

		rgba2,
		rgba8,
		rgba12,
		rgba16,

		rg8,
		rg32,
		rg32i,

		r8,
		r8i,
		r32,
		r32i,
		r32ui,

		bgr8,
		argb8,

		depth24stencil8,
		depth32stencil8,

		depth16,
		depth32,

		shadow16,
		shadow32
	  
	};
	TextureFormat (InternalFormat format);

	InternalFormat Internal;
public:
	const static TextureFormat RGB4;
	const static TextureFormat RGB5;
	const static TextureFormat RGB8;
	const static TextureFormat RGB10;
	const static TextureFormat RGB12;
	const static TextureFormat RGB16;
	const static TextureFormat RGBA2;
	const static TextureFormat RGBA8;
	const static TextureFormat RGBA12;
	const static TextureFormat RGBA16;

	const static TextureFormat RG8;
	const static TextureFormat RG32;
	const static TextureFormat RG32i;

	const static TextureFormat R8;
	const static TextureFormat R8i;
	const static TextureFormat R32i;
	const static TextureFormat R32ui;
	const static TextureFormat R32;
	

	const static TextureFormat BGR8;
	const static TextureFormat ARGB8;

	const static TextureFormat Depth24Stencil8;
	const static TextureFormat Depth32Stencil8;

	const static TextureFormat Depth16;
	const static TextureFormat Depth32;

	const static TextureFormat Shadow16;
	const static TextureFormat Shadow32;

	bool IsSupported () const;
	std::string ToString () const;

	unsigned int InternalGLFormat () const;
	unsigned int Format () const;
	unsigned int Type () const;

	bool IsIntegerFormat() const;
	bool IsShadowFormat() const;

	bool operator ==  (const TextureFormat &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const TextureFormat &op2) const {return Internal != op2.Internal;}
};

class TextureDataFormat
{
	enum InternalFormat
	{
		r8,
		rg8,
		rgb8,
		rgba8,
		bgr8,
		bgra8,
		depthf,
	};
	InternalFormat Internal;

	TextureDataFormat (InternalFormat format);

public:
	const static TextureDataFormat R8;
	const static TextureDataFormat RG8;
	const static TextureDataFormat RGB8;
	const static TextureDataFormat RGBA8;
	const static TextureDataFormat BGR8;
	const static TextureDataFormat BGRA8;
	const static TextureDataFormat DepthFloat;

	unsigned int DataType () const;
	unsigned int Format () const;

	bool operator ==  (const TextureDataFormat &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const TextureDataFormat &op2) const {return Internal != op2.Internal;}

	std::string ToString () const;
};

class TextureFiltering
{
	enum InternalEnum
	{
		none,
		mipmapping,
		anisotropic
	};
	InternalEnum Internal;

	TextureFiltering (InternalEnum format)
		: Internal(format)
	{}

public:
	const static TextureFiltering None;
	const static TextureFiltering Anisotropic;
	const static TextureFiltering MipMapping;

	bool IsSupported () const;

	bool operator ==  (const TextureFiltering &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const TextureFiltering &op2) const {return Internal != op2.Internal;}

	std::string ToString () const;
};

}}

