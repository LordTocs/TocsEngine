#include "Image2D.h"
#include <iostream>
#include <CL/cl.h>
#include <cl/cl_gl.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/GLHeader.h>
#include "ErrorCheck.h"
using namespace std;

namespace Tocs {
namespace Parallel {

Image2D::Image2D(unsigned int width, unsigned int height, const ImageFormat &format, const BufferAccess &access, Context &context)
	: ImagePtr (nullptr), Format(format)
{
	int error;
	cl_image_format clformat = {format.ChannelOrder (), format.ChannelType ()};
	ImagePtr = clCreateImage2D (context.GetCLPtr (),access.GetCLEnum (),&clformat,width,height,0,nullptr,&error);
	if (CheckError(error))
	{
		cout << "Failed to create image." << endl;
	}
}

Image2D::Image2D(Tocs::Graphics::Texture2D &linkme, const BufferAccess &access, Context &context)
	: ImagePtr (nullptr), Format(ImageFormat::A16S)
{
	int error;
	ImagePtr = clCreateFromGLTexture2D (context.GetCLPtr (),access.GetCLEnum (),GL_TEXTURE_2D,0,linkme.GetID (), &error);
	if (CheckError(error))
	{
		cout << "Failed to create image from GL image." << endl;
	}
}

Image2D::Image2D(Image2D &&moveme)
	: ImagePtr(moveme.ImagePtr), Format(moveme.Format)
{
	moveme.ImagePtr = nullptr;
}

Image2D::~Image2D(void)
{
	clReleaseMemObject (ImagePtr);
}

Image2D &Image2D::operator= (Image2D &&moveme)
{
	Format = moveme.Format;
	ImagePtr = moveme.ImagePtr;
	moveme.ImagePtr = nullptr;
	return *this;
}

unsigned int Image2D::Width () const
{
	unsigned int result;
	clGetImageInfo (ImagePtr,CL_IMAGE_WIDTH,sizeof(result),&result,nullptr);
	return result;
}
unsigned int Image2D::Height () const
{
	unsigned int result;
	clGetImageInfo (ImagePtr,CL_IMAGE_HEIGHT,sizeof(result),&result,nullptr);
	return result;
}

}}