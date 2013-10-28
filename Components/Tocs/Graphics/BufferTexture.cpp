#include "BufferTexture.h"
#include "GLHeader.h"
namespace Tocs {
namespace Graphics {

BufferTexture::BufferTexture(const TBO &buffer, TextureFormat format)
	: ID (0)
{
	glGenTextures (1,&ID);
	glBindTexture (GL_TEXTURE_BUFFER, ID);
	GLErrorCheck();
	glTexBuffer (GL_TEXTURE_BUFFER,format.InternalGLFormat(),buffer.GetID());
	GLErrorCheck ();
	glBindTexture (GL_TEXTURE_BUFFER, 0);
}

BufferTexture::BufferTexture(BufferTexture &&moveme)
	: ID (moveme.ID)
{
	moveme.ID = 0;
}

BufferTexture::~BufferTexture()
{
	glDeleteTextures(1,&ID);
}

void BufferTexture::Bind () const
{
	glBindTexture (GL_TEXTURE_2D,ID);
	GLErrorCheck ();
}

void BufferTexture::Bind (int Register) const
{
	glActiveTexture (GL_TEXTURE0 + Register);
	GLErrorCheck ();
	glBindTexture (GL_TEXTURE_2D,ID);
	GLErrorCheck ();
}

void BufferTexture::UnBind () const
{
#ifdef _DEBUG
	glBindTexture (GL_TEXTURE_2D,0);
	GLErrorCheck ();
#endif
}

}}