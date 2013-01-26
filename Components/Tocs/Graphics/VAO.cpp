#include "VAO.h"
#include "GLHeader.h"

namespace Tocs {
namespace Graphics {

VAO::VAO()
	: ID (0)
{
	glGenVertexArrays (1,&ID);
}

VAO::VAO(VAO &&moveme)
	: ID(moveme.ID)
{
	moveme.ID = 0;
}

VAO::~VAO()
{
	glDeleteVertexArrays (1,&ID);
}

void VAO::Bind () const 
{
	glBindVertexArray (ID);
	GLErrorCheck ();
}

void VAO::UnBind () const
{
	glBindVertexArray (0);
	GLErrorCheck ();
}

void VAO::AddVBO (const VBO &vbo, const VertexFormat &format)
{
	//Bind ();
	vbo.Bind ();
	format.Apply ();
	vbo.UnBind ();
	//UnBind ();
}

}}