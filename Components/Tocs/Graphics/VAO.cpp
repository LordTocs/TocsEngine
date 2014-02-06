#include "VAO.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {

VAO::VAO()
	: ID(0), Format(IndexFormat::ThirtyTwoBit)
{
	glGenVertexArrays (1,&ID);
	GLErrorCheck ();
}

VAO::VAO(VAO &&moveme)
	: ID(moveme.ID), Format(moveme.Format)
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
	Format = moveme.Format;
	moveme.ID = 0;
	return *this;
}

VAO::~VAO()
{
	glDeleteVertexArrays (1,&ID);
	GLErrorCheck ();
}

void VAO::Bind () const 
{
	GLErrorCheck();
	glBindVertexArray (ID);
	GLErrorCheck ();
}

void VAO::UnBind () const
{
	glBindVertexArray (0);
	GLErrorCheck ();
}

void VAO::AddVBO (const BufferBase &vbo, const VertexFormat &format)
{
	vbo.Bind (BufferTarget::Vertex);
	format.Apply ();
	vbo.UnBind ();
}

void VAO::AddStd140VBO(const BufferBase &vbo, const VertexFormat &format)
{
	vbo.Bind(BufferTarget::Vertex);
	format.ApplyStd140();
	vbo.UnBind();
}


void VAO::AddIBO(const Buffer<unsigned int> &ibo)
{
	ibo.Bind(BufferTarget::Index);
	Format = IndexFormat::ThirtyTwoBit;
}
void VAO::AddIBO(const Buffer<unsigned short> &ibo)
{
	ibo.Bind(BufferTarget::Index);
	Format = IndexFormat::SixteenBit;
}

void VAO::AddIBO(const BufferBase &ibo, const IndexFormat &format)
{
	ibo.Bind(BufferTarget::Index);
	Format = format;
}

}}