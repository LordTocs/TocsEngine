#include "RenderTarget.h"
#include "GLHeader.h"
#include <algorithm>

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

void RenderTarget::AddBufferFlag(int flag)
{
	auto i = std::lower_bound(BufferList.begin(), BufferList.end(), flag);
	
	if (i != BufferList.end() && (*i) == flag)
	{
		return;
	}

	BufferList.insert(i, flag);
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
	AddBufferFlag (GL_COLOR_ATTACHMENT0 + output);
	UnBind ();
}

void RenderTarget::SetCubeMapArraySide(const CubeMapArray &arr, int layer, int face, int output)
{
	InternalBind();
	glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + output, GL_TEXTURE_CUBE_MAP_ARRAY, arr.GetID(),0,layer*6 + face);
	GLErrorCheck();
	AddBufferFlag(GL_COLOR_ATTACHMENT0 + output);
	UnBind();
}

void RenderTarget::SetDepthCubeMapArraySide(const CubeMapArray &arr, int layer, int face)
{
	InternalBind();
	glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, arr.GetID(), 0, layer * 6 + face);
	GLErrorCheck();
	UnBind();
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
	else if (result == /*GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS*/ 0x8CD9)
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
