#include "RenderTarget.h"
#include "GLHeader.h"


namespace Tocs {
namespace Graphics {

RenderTarget::RenderTarget(void)
	: ID (0)
{
	glGenFramebuffers (1, (GLuint *)&ID);
	GLErrorCheck ();
}


RenderTarget::~RenderTarget(void)
{
	glDeleteFramebuffers (1, (GLuint *)&ID);
	GLErrorCheck ();
}

void RenderTarget::InternalBind ()
{
	glBindFramebuffer (GL_FRAMEBUFFER, ID);
	GLErrorCheck ();
}

void RenderTarget::Bind ()
{
	InternalBind ();
	if (BufferList.size () > 0)
	{
		glDrawBuffers (BufferList.size (),(GLenum *)&BufferList[0]);
		GLErrorCheck ();
	}
}

void RenderTarget::UnBind ()
{
	glBindFramebuffer (GL_FRAMEBUFFER, 0);
	GLErrorCheck ();
	glDrawBuffer(GL_BACK);
	GLErrorCheck();
}

void RenderTarget::SetTexture (const Texture2D &texture, int output)
{
	InternalBind ();
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + output,GL_TEXTURE_2D,texture.GetID (),0);
	GLErrorCheck ();
	BufferList.push_back (GL_COLOR_ATTACHMENT0 + output);
	UnBind ();
}

void RenderTarget::SetDepthBuffer (const DepthStencilBuffer &texture)
{
	InternalBind ();
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,texture.GetID (),0);
	GLErrorCheck ();
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D,texture.GetID (),0);
	GLErrorCheck ();
	UnBind ();
}

void RenderTarget::DebugCompleteness ()
{
	InternalBind ();

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (result == GL_FRAMEBUFFER_COMPLETE)
		return;
	std::cout << "RenderTarget not complete: ";
	if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
	{
		std::cout << "Incomplete Attachment";
	}
	else if (result == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS)
	{
		std::cout << "Incompatible dimensions";
	}
	else if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
	{
		std::cout << "Missing attachment.";
	}
	else if (result == GL_FRAMEBUFFER_UNSUPPORTED)
	{
		std::cout << " Framebuffer's Unsupported.";
	}
	UnBind ();
}

}}
