#include "UBO.h"
#include "GLHeader.h"
namespace Tocs {
namespace Graphics {

UBO::UBO(unsigned int size)
	: ID (0)
{
	glGenBuffers (1, &ID);

	Bind ();

	glBufferData (GL_UNIFORM_BUFFER, size,nullptr,GL_DYNAMIC_DRAW);
	GLErrorCheck();
	UnBind ();
}

UBO::UBO(UBO &&moveme)
	: ID (moveme.ID)
{
	moveme.ID = 0;
}

UBO::~UBO()
{
	glDeleteBuffers(1,&ID);
}

UBO &UBO::operator= (UBO &&moveme)
{
	glDeleteBuffers(1,&ID);
	ID = moveme.ID;
	moveme.ID = 0;
	return *this;
}


void UBO::Bind () const
{
	glBindBuffer (GL_UNIFORM_BUFFER, ID);
	GLErrorCheck();
}

void UBO::Bind (unsigned int index) const
{
	glBindBufferBase (GL_UNIFORM_BUFFER,index,ID);
	GLErrorCheck ();
}

void UBO::UnBind () const
{
#ifdef _DEBUG
	glBindBuffer (GL_UNIFORM_BUFFER, 0);
	GLErrorCheck();
#endif
}

void UBO::WriteData (unsigned char *data, unsigned int bytes)
{
	Bind ();

	glBufferSubData(GL_UNIFORM_BUFFER, 0, bytes,data);
	GLErrorCheck();
	UnBind ();
}

void UBO::WriteData (unsigned char *data, unsigned int bytes, unsigned int offset)
{
	Bind ();

	glBufferSubData(GL_UNIFORM_BUFFER, offset  , bytes,data);
	GLErrorCheck();
	UnBind ();
}

}}

