#include "DepthStencilBuffer.h"
#include "GLHeader.h"
#include <Tocs/Drawing/Image.h>

namespace Tocs {
namespace Graphics {

const DepthStencilFormat DepthStencilFormat::D24S8 (depth24stencil8);
const DepthStencilFormat DepthStencilFormat::D32S8 (depth32stencil8);

unsigned int DepthStencilFormat::InternalGLFormat () const
{
	switch (Internal)
	{
	case depth24stencil8:
		return GL_DEPTH24_STENCIL8;
	case depth32stencil8:
		return GL_DEPTH32F_STENCIL8;
	}
}
unsigned int DepthStencilFormat::Format () const
{
	return GL_DEPTH_STENCIL;
}
unsigned int DepthStencilFormat::Type () const
{
	switch (Internal)
	{
	case depth24stencil8:
		return GL_UNSIGNED_INT_24_8;
	case depth32stencil8:
		return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
	}
}

DepthStencilBuffer::DepthStencilBuffer(int width, int height, const DepthStencilFormat &format)
	: _Width(width), _Height(height), _Format (format)
{
	glGenTextures (1,&ID);
	BuildBuffer (width,height,format);
}

DepthStencilBuffer::DepthStencilBuffer(DepthStencilBuffer &&moveme)
	: _Width(moveme._Width), _Height(moveme._Height), _Format(moveme._Format), ID(moveme.ID)
{
	moveme.ID = 0;
	moveme._Width = 0;
	moveme._Height = 0;
}

DepthStencilBuffer::~DepthStencilBuffer()
{
	glDeleteTextures (1,&ID);
	GLErrorCheck ();
}

void DepthStencilBuffer::BuildBuffer (int width, int height, const DepthStencilFormat &format)
{
	Bind ();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GLErrorCheck ();
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLErrorCheck ();
	glTexImage2D (GL_TEXTURE_2D,0,format.InternalGLFormat (), width, height,0,format.Format (),format.Type(),nullptr);
	GLErrorCheck ();
	UnBind ();
}

void DepthStencilBuffer::Bind () const
{
	glBindTexture (GL_TEXTURE_2D,ID);
	GLErrorCheck ();
}

void DepthStencilBuffer::Bind (int Register) const
{
	glActiveTexture (GL_TEXTURE0 + Register);
	GLErrorCheck ();
	glBindTexture (GL_TEXTURE_2D,ID);
	GLErrorCheck ();
}
void DepthStencilBuffer::UnBind () const
{
	glBindTexture (GL_TEXTURE_2D,0);
	GLErrorCheck ();
}

void DepthStencilBuffer::SaveDebug(const std::string &filename)
{
	//Drawing::Image img(Width(), Height());
	//
	//ReadData(TextureDataFormat::RGBA8, &img(0, 0));
	//
	//for (int y = 0; y < Height(); ++y)
	//{
	//	for (int x = 0; x < Width(); ++x)
	//	{
	//		img(x, y).A = 255;
	//	}
	//}
	//
	//img.WriteToFile(file);
}



}}