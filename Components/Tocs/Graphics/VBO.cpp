#include "VBO.h"
#include "GLHeader.h"

namespace Tocs {
namespace Graphics {

VBO::VBO(int size)
	: Size (size)
{
	Build ();
}

VBO::VBO(VBO &&moveme)
	: ID (moveme.ID),
	  Size (moveme.Size)
{
	moveme.ID = 0;
	moveme.Size = 0;
}


VBO::~VBO(void)
{
	glDeleteBuffers (1,&ID);
}

void VBO::Build ()
{
	glGenBuffers (1,&ID);
	GLErrorCheck ();
	Bind ();
	glBufferData (GL_ARRAY_BUFFER,static_cast <GLsizeiptr> (Size),nullptr, GL_DYNAMIC_DRAW);
	GLErrorCheck ();
	UnBind ();
}

void VBO::Bind () const
{
	glBindBuffer (GL_ARRAY_BUFFER,ID);
	GLErrorCheck ();
}

void VBO::UnBind () const
{
	glBindBuffer (GL_ARRAY_BUFFER,0);
	GLErrorCheck ();
}

void VBO::WriteData (void *data, int size)
{
	Bind ();
	glBufferSubData (GL_ARRAY_BUFFER, 0, size, data);
	GLErrorCheck ();
	UnBind ();
}

void VBO::WriteData (void *data, int size, int offset)
{
	Bind ();
	glBufferSubData (GL_ARRAY_BUFFER, offset, size, data);
	GLErrorCheck ();
	UnBind ();

}

}}
