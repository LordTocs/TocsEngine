#include "TextureFormat.h"
#include "GLHeader.h"

using namespace std;

namespace Tocs {
namespace Graphics {

TextureFormat::TextureFormat (InternalFormat format)
	: Internal (format)
{}

const TextureFormat TextureFormat::RGB4 (rgb4);
const TextureFormat TextureFormat::RGB5 (rgb5);
const TextureFormat TextureFormat::RGB8 (rgb8);
const TextureFormat TextureFormat::RGB10 (rgb10);
const TextureFormat TextureFormat::RGB12 (rgb12);
const TextureFormat TextureFormat::RGB16 (rgb16);
const TextureFormat TextureFormat::RGBA2 (rgba2);
const TextureFormat TextureFormat::RGBA8 (rgba8);
const TextureFormat TextureFormat::RGBA12 (rgba12);
const TextureFormat TextureFormat::RGBA16 (rgba16);
const TextureFormat TextureFormat::BGR8 (bgr8);
const TextureFormat TextureFormat::ARGB8 (argb8);
const TextureFormat TextureFormat::RG8 (rg8);
const TextureFormat TextureFormat::RG32 (rg32);
const TextureFormat TextureFormat::RG32i (rg32i);
const TextureFormat TextureFormat::R8 (r8);
const TextureFormat TextureFormat::R8i (r8i);
const TextureFormat TextureFormat::R8ui(r8ui);
const TextureFormat TextureFormat::R32 (r32);
const TextureFormat TextureFormat::R32ui(r32ui);
const TextureFormat TextureFormat::R32i (r32i);
const TextureFormat TextureFormat::Depth24Stencil8(depth24stencil8);
const TextureFormat TextureFormat::Depth32Stencil8(depth32stencil8);
const TextureFormat TextureFormat::Depth16(depth16);
const TextureFormat TextureFormat::Depth32(depth32);
const TextureFormat TextureFormat::Shadow16(shadow16);
const TextureFormat TextureFormat::Shadow32(shadow32);


bool TextureFormat::IsSupported () const
{
	return true; //FIX THIS
}

string TextureFormat::ToString () const
{
	switch (Internal)
	{
	case rgb4:
		return "RGB4";
	case rgb5:
		return "RGB5";
	case rgb8:
		return "RGB8";
	case rgb10:
		return "RGB10";
	case rgb12:
		return "RGB12";
	case rgb16:
		return "RGB16";
	case rgba2:
		return "RGBA2";
	case rgba8:
		return "RGBA8";
	case rgba12:
		return "RGBA12";
	case rgba16:
		return "RGBA16";
	case bgr8:
		return "BGR8";
	case argb8:
		return "ARGB8";
	case r32:
		return "R32";
	case r32i:
		return "R32i";
	case rg32:
		return "RG32";
	case rg32i:
		return "RG32i";
	}
}

unsigned int TextureFormat::InternalGLFormat () const
{
	switch (Internal)
	{
	case rgb4:
		return GL_RGB4;
	case rgb5:
		return GL_RGB5;
	case rgb8:
		return GL_RGB8;
	case rgb10:
		return GL_RGB10;
	case rgb12:
		return GL_RGB12;
	case rgb16:
		return GL_RGB16;
	case rgba2:
		return GL_RGBA2;
	case rgba8:
		return GL_RGBA8;
	case rgba12:
		return GL_RGBA12;
	case rgba16:
		return GL_RGBA16;
	case bgr8:
		return -1;//GL_BGR8;
	case argb8:
		return -1;//GL_ARGB8;
	case r8:
		return GL_R8;
	case r8i:
		return GL_R8I;
	case r8ui:
		return GL_R8UI;
	case rg8:
		return GL_RG8;
	case rg32:
		return GL_RG32F;
	case rg32i:
		return GL_RG32I;
	case r32ui:
		return GL_R32UI;
	case r32:
		return GL_R32F;
	case r32i:
		return GL_R32I;
	case depth24stencil8:
		return GL_DEPTH24_STENCIL8;
	case depth32stencil8:
		return GL_DEPTH32F_STENCIL8;
	case depth16:
		return GL_DEPTH_COMPONENT16;
	case depth32:
		return GL_DEPTH_COMPONENT32;
	case shadow16:
		return GL_DEPTH_COMPONENT16;
	case shadow32:
		return GL_DEPTH_COMPONENT32;
	}
}

unsigned int TextureFormat::Format () const
{
	switch (Internal)
	{
	case rgb4:
	case rgb5:
	case rgb8:
	case rgb10:
	case rgb12:
	case rgb16:
		return GL_RGB;
	case rgba2:
	case rgba8:
	case rgba12:
	case rgba16:
		return GL_RGBA;
	case bgr8:
		return GL_BGR;
	case rg32:
	case rg8:
		return GL_RG;
	case rg32i:
		return GL_RG_INTEGER;
	case r32:
	case r8:
		return GL_RED;
	case r8i:
	case r8ui:
	case r32i:
	case r32ui:
		return GL_RED_INTEGER;
	case depth24stencil8:
	case depth32stencil8:
		return GL_DEPTH_STENCIL;
	case depth16:
	case depth32:
	case shadow16:
	case shadow32:
		return GL_DEPTH_COMPONENT;
	}
	return -1;
}
unsigned int TextureFormat::Type () const
{
	switch (Internal)
	{
	case rgb4:
	case rgb5:
	case rgb8:
		return GL_UNSIGNED_BYTE;
	case rgb10:
	case rgb12:
	case rgb16:
		return GL_UNSIGNED_SHORT;
	case rgba2:
	case rgba8:
		return GL_UNSIGNED_BYTE;
	case rgba12:
	case rgba16:
		return GL_UNSIGNED_SHORT;
	case bgr8:
	case argb8:
		return GL_UNSIGNED_BYTE;//GL_ARGB8;
	case r8:
	case rg8:
		return GL_UNSIGNED_BYTE;
	case r32:
	case rg32:
		return GL_FLOAT;
	case r32i:
		return GL_INT;
	case r8i:
		return GL_BYTE;
	case r8ui:
		return GL_UNSIGNED_BYTE;
	case r32ui:
		return GL_UNSIGNED_INT;
	case depth24stencil8:
		return GL_UNSIGNED_INT_24_8;
	case depth32stencil8:
		return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
	case depth16:
	case depth32:
	case shadow16:
	case shadow32:
		return GL_FLOAT;
	}
	return -1;
}

bool TextureFormat::IsIntegerFormat() const
{
	return Internal == rg32i ||
		   Internal == r32i ||
		   Internal == r8i ||
		   Internal == r8ui ||
		   Internal == r32ui;
}

bool TextureFormat::IsShadowFormat() const
{
	return Internal == shadow16 || Internal == shadow32;
}

////////////////////////////////////////////////
///////////TextureDataFormat////////////////////
////////////////////////////////////////////////

TextureDataFormat::TextureDataFormat (InternalFormat format)
	: Internal (format)
{}

const TextureDataFormat TextureDataFormat::R8(r8);
const TextureDataFormat TextureDataFormat::RG8(rg8);
const TextureDataFormat TextureDataFormat::RGB8 (rgb8);
const TextureDataFormat TextureDataFormat::RGBA8 (rgba8);
const TextureDataFormat TextureDataFormat::BGR8 (bgr8);
const TextureDataFormat TextureDataFormat::BGRA8 (bgra8);
const TextureDataFormat TextureDataFormat::DepthFloat (depthf);

unsigned int TextureDataFormat::Format () const
{
	switch (Internal)
	{
	case r8:
		return GL_RED;
	case rg8:
		return GL_RG;
	case rgb8:
		return GL_RGB;
	case rgba8:
		return GL_RGBA;
	case bgr8:
		return GL_BGR;
	case bgra8:
		return GL_BGRA;
	case depthf:
		return GL_DEPTH_COMPONENT;
	}
}

unsigned int TextureDataFormat::DataType () const
{
	switch (Internal)
	{
	case r8:
	case rg8:
	case rgb8:
	case rgba8:
	case bgr8:
	case bgra8:
		return GL_UNSIGNED_BYTE;
	case depthf:
		return GL_FLOAT;
	}
}

string TextureDataFormat::ToString () const 
{
	switch (Internal)
	{
	case rgb8:
		return "RGB8";
	case rgba8:
		return "RGBA8";
	case bgr8:
		return "BGR8";
	case bgra8:
		return "BGRA8";
	case depthf:
		return "DepthFloat";
	}
}

///////////////////////////////////////////////////
////////Texture Filtering//////////////////////////
///////////////////////////////////////////////////

const TextureFiltering TextureFiltering::None (none);
const TextureFiltering TextureFiltering::MipMapping (mipmapping);
const TextureFiltering TextureFiltering::Anisotropic (anisotropic);

bool TextureFiltering::IsSupported () const
{
	return true;
}

string TextureFiltering::ToString () const
{
	switch (Internal)
	{
	case none:
		return "None";
	case mipmapping:
		return "MipMapping";
	case anisotropic:
		return "Anisotropic";
	}
}

}}