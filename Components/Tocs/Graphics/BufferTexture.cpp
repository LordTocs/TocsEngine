#include "BufferTexture.h"
#include "GLHeader.h"
namespace Tocs {
namespace Graphics {

BufferTexture::BufferTexture(const BufferBase &buffer, TextureFormat format)
: ID(0), Format(format)
{
	glGenTextures (1,&ID);
	glBindTexture (GL_TEXTURE_BUFFER, ID);
	GLErrorCheck();
	glTexBuffer (GL_TEXTURE_BUFFER,format.InternalGLFormat(),buffer.GetID());
	GLErrorCheck ();
	glBindTexture (GL_TEXTURE_BUFFER, 0);
}

BufferTexture::BufferTexture(BufferTexture &&moveme)
: ID(moveme.ID), Format(moveme.Format)
{
	moveme.ID = 0;
}

BufferTexture::~BufferTexture()
{
	glDeleteTextures(1,&ID);
	GLErrorCheck();
}

void BufferTexture::Bind () const
{
	glBindTexture(GL_TEXTURE_BUFFER, ID);
	GLErrorCheck ();
}

void BufferTexture::Bind (int Register) const
{
	glActiveTexture (GL_TEXTURE0 + Register);
	GLErrorCheck ();
	glBindTexture(GL_TEXTURE_BUFFER, ID);
	GLErrorCheck ();
}

void BufferTexture::BindImage(int Register) const
{
	glBindImageTexture(Register, ID, 0, false, 0, GL_READ_WRITE, Format.InternalGLFormat());
	GLErrorCheck();
}

void BufferTexture::UnBind () const
{
#ifdef _DEBUG
	glBindTexture(GL_TEXTURE_BUFFER, 0);
	GLErrorCheck ();
#endif
}

}}