#include "Texture.h"
#include "GLHeader.h"
#include <iostream>
#include <Freeimage.h>
#include <memory>
#include <fstream>
#include <cassert>
#include <vector>
#include <Tocs/Drawing/Image.h>
using namespace std;

namespace Tocs {
namespace Graphics {

Texture2D::Texture2D(int width, int height, const TextureFiltering &filtering, const TextureFormat &format)
	: ID (0),
	  Format_ (format),
	  Filtering_ (filtering),
	  Width_(width),
	  Height_(height)
{
	glGenTextures (1, &ID);
	GLErrorCheck();
	BuildTexture (width,height,filtering,format);
}

Texture2D::Texture2D(Texture2D &&moveme)
	: ID(moveme.ID),
	  Format_ (moveme.Format_),
	  Filtering_ (moveme.Filtering_),
	  Width_(moveme.Width_),
	  Height_(moveme.Height_)
{
	moveme.ID = 0;
	moveme.Width_ = 0;
	moveme.Height_ = 0;
}

Texture2D::~Texture2D(void)
{
	glDeleteTextures (1,&ID);
	GLErrorCheck();
}

Texture2D &Texture2D::operator= (Texture2D &&moveme)
{
	ID = moveme.ID;
	moveme.ID = 0;
	Width_ = moveme.Width_;
	moveme.Width_ = 0;
	Height_ = moveme.Height_;
	moveme.Height_ = 0;
	return *this;
}

void Texture2D::BuildTexture (int width, int height, const TextureFiltering &filtering, const TextureFormat &format)
{
	Bind ();

	Filtering_ = filtering;
	Format_ = format;

	
	
	if (!format.IsIntegerFormat())
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLErrorCheck();
		if (filtering != TextureFiltering::None)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			GLErrorCheck();
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GLErrorCheck();
		}

		if (filtering == TextureFiltering::Anisotropic)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
			GLErrorCheck();
		}
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		GLErrorCheck();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		GLErrorCheck();
	}


	if (format.IsShadowFormat())
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	GLErrorCheck ();

	glTexImage2D (GL_TEXTURE_2D,0,format.InternalGLFormat (),width,height,0,format.Format (),format.Type (),nullptr);
	GLErrorCheck ();

	UnBind ();
}

void Texture2D::SetData (TextureDataFormat format,const void *data)
{
	Bind ();
	glTexSubImage2D (GL_TEXTURE_2D,0,0,0,Width (), Height (),format.Format (),format.DataType (),data);
	GLErrorCheck ();

	//cout << "SetData: " << format.Format () << ", " << format.DataType () << endl;

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

void Texture2D::BindImage(int reg, int level) const
{
	glBindImageTexture(reg, ID, level, false, 0, GL_READ_WRITE, Format_.InternalGLFormat());
	GLErrorCheck();
}

void Texture2D::UnBind () const
{
	glBindTexture (GL_TEXTURE_2D,0);
	GLErrorCheck();
}

static inline void FlipColorOrder (unsigned char *pixeldata)
{

    unsigned char temp = pixeldata[0];

    pixeldata[0] = pixeldata[2];

    pixeldata[2] = temp;

}

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
	else
	{
		assert(false);
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

void Texture2D::ReadData(TextureDataFormat format, void *data) const
{
	Bind();
	glGetTexImage(GL_TEXTURE_2D, 0, format.Format(), format.DataType(), data);
	GLErrorCheck();
	UnBind();
}

void Texture2D::LoadRaw(TextureDataFormat format, const std::string &file)
{
	std::ifstream input(file, std::ios::binary);

	//The most vexing parse strikes again. Cheeky bastard.
	std::vector<char> buffer ((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator <char>()));

	SetData(format, &buffer[0]);
}

void Texture2D::SaveDebug(const std::string &file) const
{
	Drawing::Image img(Width(), Height());

	ReadData(TextureDataFormat::RGBA8, &img(0, 0));

	for (int y = 0; y < Height(); ++y)
	{
		for (int x = 0; x < Width(); ++x)
		{
			img(x, y).A = 255;
		}
	}

	img.WriteToFile(file);
}

}}