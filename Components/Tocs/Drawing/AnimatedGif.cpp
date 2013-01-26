#include "AnimatedGif.h"
#include <iostream>
#include <sstream>
#include <FreeImage.h>

using namespace std;

namespace Tocs {
namespace Drawing {

void AnimatedGif::AddFrame (const Image &image, float time)
{
	if (image.GetWidth () != Width || image.GetHeight () != Height)
		return; //Incompatible dimensions

	Frames.push_back(Frame(image,time));
}

void AnimatedGif::WriteToFile (const std::string &filename)
{
	cout << "Writing " << filename << "..." << endl;
	FIMULTIBITMAP *gif = nullptr;
	gif = FreeImage_OpenMultiBitmap (FIF_GIF,filename.c_str(),true,false);

	if (gif == nullptr)
		return;
	for (auto i = Frames.begin (); i != Frames.end (); ++i)
	{
		FIBITMAP *dib = nullptr;
		dib = FreeImage_ConvertFromRawBits ((BYTE*)((*i).GetImage().GetDataPtr ()),Width,Height,4*Width,32,0xFF000000,0x00FF0000,0x0000FF00,true);
		FIBITMAP *dib24bit = FreeImage_ConvertTo24Bits(dib);
		FIBITMAP *dib8bit = FreeImage_ColorQuantize(dib24bit,FIQ_WUQUANT);
		FreeImage_Unload(dib24bit);
		FreeImage_Unload(dib);
		if (dib == nullptr)
		{
			cout << "Failed to create DIB." << endl;
		}
		
		FreeImage_SetMetadata(FIMD_ANIMATION, dib8bit,nullptr,nullptr);
		unsigned int frametime = (*i).GetTime ()*1000;
		
		FITAG *tag = FreeImage_CreateTag();
		FreeImage_SetTagKey(tag,"FrameTime");
		FreeImage_SetTagType(tag, FIDT_LONG);
		FreeImage_SetTagCount(tag,1);
		FreeImage_SetTagLength(tag,4);
		FreeImage_SetTagValue(tag,&frametime);
		FreeImage_SetMetadata(FIMD_ANIMATION,dib8bit,FreeImage_GetTagKey(tag),tag);


		
		FreeImage_AppendPage(gif,dib8bit);
		FreeImage_Unload(dib8bit);
		//cout << "Pages: " << FreeImage_GetPageCount (gif) << endl;
		FreeImage_DeleteTag(tag);
		//FreeImage_Unload (dib);
	}

	//cout << "Pages: " << FreeImage_GetPageCount (gif);

	FreeImage_CloseMultiBitmap(gif);
	cout << "Complete." << endl;
}

}}