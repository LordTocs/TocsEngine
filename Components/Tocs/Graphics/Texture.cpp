#include "Texture.h"
#include "GLHeader.h"
#include <iostream>
#include <Freeimage.h>
#include <memory>

using namespace std;

namespace Tocs {
namespace Graphics {

Texture2D::Texture2D(int width, int height, const TextureFiltering &filtering, const TextureFormat &format)
	: ID (0),
	  _Format (format),
	  _Filtering (filtering),
	  _Width(width),
	  _Height(height)
{
	glGenTextures (1, &ID);
	BuildTexture (width,height,filtering,format);
}

Texture2D::Texture2D(Texture2D &&moveme)
	: ID(moveme.ID),
	  _Format (moveme._Format),
	  _Filtering (moveme._Filtering),
	  _Width(moveme._Width),
	  _Height(moveme._Height)
{
	moveme.ID = 0;
	moveme._Width = 0;
	moveme._Height = 0;
}

Texture2D::~Texture2D(void)
{
	glDeleteTextures (1,&ID);
}

Texture2D &Texture2D::operator= (Texture2D &&moveme)
{
	ID = moveme.ID;
	moveme.ID = 0;
	_Width = moveme._Width;
	moveme._Width = 0;
	_Height = moveme._Height;
	moveme._Height = 0;
	return *this;
}

void Texture2D::BuildTexture (int width, int height, const TextureFiltering &filtering, const TextureFormat &format)
{
	Bind ();

	_Filtering = filtering;
	_Format = format;

	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLErrorCheck ();
	
	if (filtering != TextureFiltering::None)
	{
		glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		GLErrorCheck ();
	}
	else
	{
		glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		GLErrorCheck ();
	}

	if (filtering == TextureFiltering::Anisotropic)
	{
		glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,2.0f);
		GLErrorCheck ();
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	GLErrorCheck ();

	glTexImage2D (GL_TEXTURE_2D,0,format.InternalGLFormat (),width,height,0,format.Format (),format.Type (),nullptr);
	GLErrorCheck ();

	UnBind ();
}

void Texture2D::SetData (TextureDataFormat format, void *data)
{
	Bind ();
	glTexSubImage2D (GL_TEXTURE_2D,0,0,0,Width (), Height (),format.Format (),format.DataType (),data);
	GLErrorCheck ();

	cout << "SetData: " << format.Format () << ", " << format.DataType () << endl;

	if (Filtering () != TextureFiltering::None)
	{
		glGenerateMipmap (GL_TEXTURE_2D);
		GLErrorCheck ();
	}
	UnBind ();
}

void Texture2D::Bind () const
{
	glBindTexture (GL_TEXTURE_2D,ID);
	GLErrorCheck ();
}

void Texture2D::Bind (int reg) const
{
	glActiveTexture (GL_TEXTURE0 + reg);
	GLErrorCheck ();
	glBindTexture (GL_TEXTURE_2D,ID);
	GLErrorCheck ();
}

void Texture2D::UnBind () const
{
	glBindTexture (GL_TEXTURE_2D,0);
}

static inline void FlipColorOrder (unsigned char *pixeldata)
{

    unsigned char temp = pixeldata[0];

    pixeldata[0] = pixeldata[2];

    pixeldata[2] = temp;

}

/*
Texture2D Texture2D::LoadFromFile (const std::string &filename)
{
	FREE_IMAGE_FORMAT fif;// FreeImage_GetFileType (filename.c_str (),filename.length ());
	fif = FreeImage_GetFileType(filename.c_str());
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		fif = FIF_PNG;

	FIBITMAP *dib = nullptr;

	//Read it!
	if(FreeImage_FIFSupportsReading(fif))
	{	
		dib = FreeImage_Load(fif,filename.c_str ());
	}
	
	unsigned int Width = FreeImage_GetWidth(dib);
	unsigned int Height = FreeImage_GetHeight(dib);
	

	Texture2D result (Width,Height,TextureFiltering::Anisotropic,TextureFormat::RGBA8);


	int bpp = FreeImage_GetBPP (dib);
	if (bpp != 32)
	{
		FIBITMAP* dib32 = FreeImage_ConvertTo32Bits (dib);
		FreeImage_Unload(dib);
		dib = dib32;
	}

	BYTE* bits = FreeImage_GetBits(dib);
	result.SetData (TextureDataFormat::RGBA8,bits);

	FreeImage_Unload(dib);

	return result;
}*/
Texture2D Texture2D::LoadFromFile (const std::string &filename)
{

	FREE_IMAGE_FORMAT fif;// FreeImage_GetFileType (filename.c_str (),filename.length ());
	fif = FreeImage_GetFileType(filename.c_str());
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
	fif = FreeImage_GetFIFFromFilename(filename.c_str());
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
	fif = FIF_PNG;



	FIBITMAP *dib = nullptr;
	//Read it!

	if(FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif,filename.c_str ());
	}


	unsigned int Width = FreeImage_GetWidth(dib);
	unsigned int Height = FreeImage_GetHeight(dib);

	Texture2D result (Width,Height,TextureFiltering::Anisotropic,TextureFormat::RGBA8);


	std::unique_ptr<unsigned char[]> Bits (new unsigned char[4*Width*Height]);
	FreeImage_ConvertToRawBits(Bits.get(), dib, 4*Width, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK,false);

    

	for (unsigned char *pixel = Bits.get(); pixel < Bits.get() + (4*(Width*Height)); pixel += 4)
	{
		FlipColorOrder(pixel);
	}

	result.SetData (TextureDataFormat::RGBA8,Bits.get());
	FreeImage_Unload(dib);
	return result;
}
}}