#include "VAO.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {

VAO::VAO()
	: ID (0)
{
	glGenVertexArrays (1,&ID);
	//cout << "VAO: Gen: " << ID << endl;
	GLErrorCheck ();
}

VAO::VAO(VAO &&moveme)
	: ID(moveme.ID)
{
	moveme.ID = 0;
}

VAO &VAO::operator= (VAO &&moveme)
{
	if (ID != 0)
	{
		glDeleteVertexArrays(1,&ID);
		GLErrorCheck ();
	}
	ID = moveme.ID;
	moveme.ID = 0;
	return *this;
}

VAO::~VAO()
{
	glDeleteVertexArrays (1,&ID);
	//cout << "VAO: Del: " << ID << endl;
	GLErrorCheck ();
}

void VAO::Bind () const 
{
	GLErrorCheck();
	glBindVertexArray (ID);
	//cout << "VAO: Bind: " << ID << endl;
	GLErrorCheck ();
}

void VAO::UnBind () const
{
	glBindVertexArray (0);
	//cout << "VAO: Unbind" << endl;
	GLErrorCheck ();
}

void VAO::AddVBO (const VBO &vbo, const VertexFormat &format)
{
	vbo.Bind ();
	format.Apply ();
	vbo.UnBind ();
}



}}