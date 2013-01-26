#include "Image3D.h"
#include <Tocs/Graphics/Texture3D.h>
#include <iostream>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <Tocs/Graphics/GLHeader.h>
#include "ErrorCheck.h"
using namespace std;

namespace Tocs {
namespace Parallel {

Image3D::Image3D(unsigned int width, unsigned int height, unsigned int depth, const ImageFormat &format, const BufferAccess &access, Context &context)
	: Format (format),
	  ImagePtr(nullptr)
{
	int error;
	cl_image_format clformat = {format.ChannelOrder (), format.ChannelType ()};
	ImagePtr = clCreateImage3D (context.GetCLPtr (),access.GetCLEnum (),&clformat,width,height,depth,0,0,nullptr,&error);
	if (CheckError(error))
	{
		cout << "Failed to create 3D image." << endl;
	}
}


Image3D::Image3D(Graphics::Texture3D &linkme,const BufferAccess &access, Context &context)
	: Format(ImageFormat::A16S), ImagePtr(nullptr)
{
	int error;
	ImagePtr = clCreateFromGLTexture3D (context.GetCLPtr (),access.GetCLEnum (),GL_TEXTURE_3D,0,linkme.GetID (),&error);
	if (CheckError(error))
	{
		cout << "Failed to create 3D image." << endl;
	}
}

Image3D::Image3D (Image3D &&moveme)
	: Format (moveme.Format),
	  ImagePtr (moveme.ImagePtr)
{
	moveme.ImagePtr = nullptr;
}

Image3D::~Image3D(void)
{
	clReleaseMemObject (ImagePtr);
}

Image3D &Image3D::operator= (Image3D &&moveme)
{
	ImagePtr = moveme.ImagePtr;
	Format = moveme.Format;
	moveme.ImagePtr = nullptr;
	return *this;
}


unsigned int Image3D::Width () const
{
	unsigned int result;
	clGetImageInfo (ImagePtr,CL_IMAGE_WIDTH,sizeof(result),&result,nullptr);
	return result;
}
unsigned int Image3D::Height () const
{
	unsigned int result;
	clGetImageInfo (ImagePtr,CL_IMAGE_HEIGHT,sizeof(result),&result,nullptr);
	return result;
}
unsigned int Image3D::Depth () const
{
	unsigned int result;
	clGetImageInfo (ImagePtr,CL_IMAGE_DEPTH,sizeof(result),&result,nullptr);
	return result;
}

}}