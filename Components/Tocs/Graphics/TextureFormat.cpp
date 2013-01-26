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
const TextureFormat TextureFormat::R32 (r32);

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
	case r32:
		return GL_R32F;
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
	case r32:
		return GL_RED;
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
	case r32:
		return GL_FLOAT;
	}
	return -1;
}

////////////////////////////////////////////////
///////////TextureDataFormat////////////////////
////////////////////////////////////////////////

TextureDataFormat::TextureDataFormat (InternalFormat format)
	: Internal (format)
{}

const TextureDataFormat TextureDataFormat::RGB8 (rgb8);
const TextureDataFormat TextureDataFormat::RGBA8 (rgba8);
const TextureDataFormat TextureDataFormat::BGR8 (bgr8);
const TextureDataFormat TextureDataFormat::BGRA8 (bgra8);
const TextureDataFormat TextureDataFormat::DepthFloat (depthf);

unsigned int TextureDataFormat::Format () const
{
	switch (Internal)
	{
	case rgb8:
		return GL_RGB;
	case rgba8:
		return GL_RGBA;
	case bgr8:
		return GL_BGR;
	case bgra8:
		return GL_BGRA;
	case depthf:
		return GL_FLOAT;
	}
}

unsigned int TextureDataFormat::DataType () const
{
	switch (Internal)
	{
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