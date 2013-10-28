#include "TBO.h"
#include "GLHeader.h"

namespace Tocs {
namespace Graphics {

TBO::TBO (unsigned int bytes)
	: ID (0)
{
	Build (bytes);
}

void TBO::Build (unsigned int bytes)
{
	glGenBuffers (1, &ID);

	Bind ();

	glBufferData (GL_TEXTURE_BUFFER, bytes,nullptr,GL_STATIC_DRAW);
	GLErrorCheck();
	UnBind ();
}

TBO::TBO(TBO &&moveme)
	: ID(moveme.ID)
{
	moveme.ID = 0;
}

TBO::~TBO()
{
	glDeleteBuffers (1, &ID);
	GLErrorCheck();
}

TBO &TBO::operator= (TBO &&moveme)
{
	glDeleteBuffers (1,&ID);
	GLErrorCheck();
	ID = moveme.ID;
	moveme.ID = 0;
	return *this;
}

void TBO::Bind ()
{
	glBindBuffer (GL_TEXTURE_BUFFER, ID);
	GLErrorCheck();
}

void TBO::UnBind ()
{
#ifdef _DEBUG
	glBindBuffer (GL_TEXTURE_BUFFER, 0);
	GLErrorCheck();
#endif
}

void TBO::WriteData (unsigned char *data, unsigned int bytes)
{
	Bind ();

	glBufferSubData(GL_TEXTURE_BUFFER, 0, bytes,data);
	GLErrorCheck();
	UnBind ();
}

void TBO::WriteData (unsigned char *data, unsigned int bytes, unsigned int offset)
{
	Bind ();

	glBufferSubData(GL_TEXTURE_BUFFER, offset  , bytes,data);
	GLErrorCheck();
	UnBind ();
}

}}