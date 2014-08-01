#include "TextureCompiler.h"
#include <squish.h>
#include <FreeImage.h>
#include <iostream>
#include <memory>

namespace Tocs {
namespace AssetCompiler {

bool TextureCompiler::Compile(const std::string &infile, const std::string &outfile)
{

	FREE_IMAGE_FORMAT fif;// FreeImage_GetFileType (filename.c_str (),filename.length ());
	fif = FreeImage_GetFileType(infile.c_str());
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(infile.c_str());
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		fif = FIF_PNG;



	FIBITMAP *dib = nullptr;
	//Read it!

	if (FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif, infile.c_str());
	}
	else
	{
		std::cout << "Error: Format unsupported by FreeImage" << std::endl;
		return false;
	}

	if (!dib)
	{
		std::cout << "Error: Unable to load file " << infile << std::endl;
		return false;
	}


	unsigned int Width = FreeImage_GetWidth(dib);
	unsigned int Height = FreeImage_GetHeight(dib);

	if (Compressed)
	{
		//Checks for size
		if (Width % 4 != 0)
		{
			std::cout << "DXTn Compression only supports widths that are multiples of 4" << std::endl;
			FreeImage_Unload(dib);
			return false;
		}
		if (Height % 4 != 0)
		{
			std::cout << "DXTn Compression only supports heights that are multiples of 4" << std::endl;
			FreeImage_Unload(dib);
			return false;
		}
	}


	std::unique_ptr<unsigned char[]> Bits(new unsigned char[4 * Width*Height]);
	FreeImage_ConvertToRawBits(Bits.get(), dib, 4 * Width, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, false);



	//for (unsigned char *pixel = Bits.get(); pixel < Bits.get() + (4 * (Width*Height)); pixel += 4)
	//{
	//	FlipColorOrder(pixel);
	//}

	FreeImage_Unload(dib);
	

	return true;
}

}
}