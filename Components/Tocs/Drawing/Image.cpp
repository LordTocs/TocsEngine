#include "Image.h"
#include <FreeImage.h>
#include <iostream>



using namespace std;
using namespace Tocs;
using namespace Tocs::Math;

namespace Tocs {
namespace Drawing {

Image::Image(unsigned int width, unsigned int height)
	: Width(width), Height(height), ColorArray(new Color[width*height])
{}

Image::Image(Image &&moveme)
	: Width(moveme.Width), Height(moveme.Height), ColorArray(std::move(moveme.ColorArray))
{

}
Image::Image(const Image &copyme)
	: Width(copyme.Width), Height(copyme.Height), ColorArray(new Color[copyme.Width*copyme.Height])
{
	std::memcpy (ColorArray.get(),copyme.ColorArray.get(),sizeof(Color) * Width * Height);
}

void Image::WriteToFile (const std::string &filename) const
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
	dib = FreeImage_ConvertFromRawBits ((BYTE*)ColorArray.get(),Width,Height,4*Width,32,0xFF000000,0x00FF0000,0x0000FF00,true);
	
	if (!dib)
	{
		cout << "Oh crap this is null" << endl;
	}

	FreeImage_Save (fif,dib,filename.c_str (),0);

	FreeImage_Unload (dib);
}

Image Image::FromFile (const std::string &filename)
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
	

	Image result (Width,Height);


	int bpp = FreeImage_GetBPP (dib);
	if (bpp != 32)
	{
		FIBITMAP* dib32 = FreeImage_ConvertTo32Bits (dib);
		FreeImage_Unload(dib);
		dib = dib32;
	}

	BYTE* bits = FreeImage_GetBits(dib);
	memcpy (result.ColorArray.get(),bits,Width*Height*(bpp/8));

	FreeImage_Unload(dib);

	return result;
}

}}