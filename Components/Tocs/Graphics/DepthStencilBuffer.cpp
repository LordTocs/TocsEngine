#include "DepthStencilBuffer.h"
#include "GLHeader.h"

namespace Tocs {
namespace Graphics {

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
}

void DepthStencilBuffer::BuildBuffer (int width, int height, const DepthStencilFormat &format)
{
	Bind ();

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D (GL_TEXTURE_2D,0,format.Format (),width, height,0,0,0,nullptr);

	UnBind ();
}

void DepthStencilBuffer::Bind () const
{
	glBindTexture (GL_TEXTURE_2D,ID);
}

void DepthStencilBuffer::Bind (int Register) const
{
	glActiveTexture (GL_TEXTURE0 + Register);
	glBindTexture (GL_TEXTURE_2D,ID);
}
void DepthStencilBuffer::UnBind () const
{
}

}}