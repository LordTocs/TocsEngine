#include "TextureArray.h"
#include "GLHeader.h"
#include <fstream>
#include <cassert>
#include <Tocs/Math/Color.h>
#include <Freeimage.h>
namespace Tocs {
namespace Graphics {

TextureArray::TextureArray(unsigned int layers, unsigned int width, unsigned int height, TextureFormat format, TextureFiltering filtering)
: ID(0), Filtering_(filtering), Format_(format), Width_(width), Height_(height)
{
	Build(layers, width, height, format, filtering);
}
TextureArray::~TextureArray()
{
	glDeleteTextures(1, &ID);
}

TextureArray::TextureArray(TextureArray &&moveme)
: ID(moveme.ID), Filtering_(std::move(moveme.Filtering_)), Format_(std::move(moveme.Format_))
{
	moveme.ID = 0;
}
TextureArray &TextureArray::operator= (TextureArray &&moveme)
{
	ID = moveme.ID;
	moveme.ID = 0;
	return *this;
}


void TextureArray::Build(unsigned int layers, unsigned int width, unsigned int height, TextureFormat format, TextureFiltering filtering)
{
	if (ID == 0)
	{
		glGenTextures(1, &ID);
	}

	Bind();

	if (!format.IsIntegerFormat())
	{
		glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLErrorCheck();
		if (filtering != TextureFiltering::None)
		{
			glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			GLErrorCheck();
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GLErrorCheck();
		}

		if (filtering == TextureFiltering::Anisotropic)
		{
			glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f);
			GLErrorCheck();
		}
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		GLErrorCheck();
		glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		GLErrorCheck();
	}

	if (format.IsShadowFormat())
	{
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		GLErrorCheck();
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		GLErrorCheck();
	}



	//Faces
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format.InternalGLFormat(), width, height, layers, 0, format.Format(), format.Type(), nullptr);
	GLErrorCheck();


	UnBind();
}


void TextureArray::Bind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
	GLErrorCheck();
}

void TextureArray::Bind(int reg) const
{
	glActiveTexture(GL_TEXTURE0 + reg);
	GLErrorCheck();
	glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
	GLErrorCheck();
}

void TextureArray::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	GLErrorCheck();
}


void TextureArray::SetData(TextureDataFormat format, const void *data, unsigned int layer)
{
	Bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Width(), Height(), format.Format(), format.DataType(), data);
	GLErrorCheck();

	//cout << "SetData: " << format.Format () << ", " << format.DataType () << endl;

	if (Filtering() != TextureFiltering::None)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		GLErrorCheck();
	}
	UnBind();
}


void TextureArray::Read(void *data, TextureDataFormat dataformat) const
{
	Bind();
	glGetTexImage(GL_TEXTURE_2D_ARRAY, 0, dataformat.Format(), dataformat.DataType(), data);
	GLErrorCheck();
	UnBind();
}

static inline void FlipColorOrder(unsigned char *pixeldata)
{

	unsigned char temp = pixeldata[0];

	pixeldata[0] = pixeldata[2];

	pixeldata[2] = temp;

}

TextureArray TextureArray::LoadFromFile(const std::string &filename)
{
	std::ifstream declfile(filename);
	if (!declfile.is_open())
	{
		assert(false && "Can't open file");
	}

	std::vector<std::string> files;
	std::string line;
	while (declfile.good())
	{
		std::getline(declfile, line);
		files.push_back(line);
	}
	declfile.close();

	unsigned int width = 0;
	unsigned int height = 0;

	std::unique_ptr<TextureArray> result;

	for (unsigned int i = 0; i < files.size(); ++i)
	{
		FREE_IMAGE_FORMAT fif;// FreeImage_GetFileType (filename.c_str (),filename.length ());
		fif = FreeImage_GetFileType(filename.c_str());
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename.c_str());
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			fif = FIF_PNG;



		FIBITMAP *dib = nullptr;
		//Read it!

		if (FreeImage_FIFSupportsReading(fif))
		{
			dib = FreeImage_Load(fif, filename.c_str());
		}
		else
		{
			assert(false);
		}


		unsigned int Width = FreeImage_GetWidth(dib);
		unsigned int Height = FreeImage_GetHeight(dib);

		if (width == 0)
			width = Width;
		else if (Width != width)
		{
			assert(false && "Dimensions don't match");
		}
		if (height == 0)
		{
			height = Height;
			result.reset(new TextureArray(files.size(), width, height, TextureFormat::RGBA8, TextureFiltering::MipMapping));
		}
		else if (Height != height)
		{
			assert(false && "Dimensions don't match");
		}



		std::unique_ptr<unsigned char[]> Bits(new unsigned char[4 * Width*Height]);
		FreeImage_ConvertToRawBits(Bits.get(), dib, 4 * Width, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, false);



		for (unsigned char *pixel = Bits.get(); pixel < Bits.get() + (4 * (Width*Height)); pixel += 4)
		{
			FlipColorOrder(pixel);
		}

		
		result->SetData(TextureDataFormat::RGBA8, Bits.get(), i);

		FreeImage_Unload(dib);
	}

	return std::move(*result.get());
}

}
}

