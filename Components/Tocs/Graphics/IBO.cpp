#include "IBO.h"
#include "GLHeader.h"
#include <iostream>

using namespace std;

namespace Tocs {
namespace Graphics {

const IndexFormat IndexFormat::SixteenBit(sixteen);
const IndexFormat IndexFormat::ThirtyTwoBit(thirtytwo);

unsigned int IndexFormat::GetSize () const
{
	switch (Internal)
	{
	case sixteen:
		return 2;
	case thirtytwo:
		return 4;
	}
}

int IndexFormat::GLType () const
{
	switch (Internal)
	{
	case sixteen:
		return GL_UNSIGNED_SHORT;
	case thirtytwo:
		return GL_UNSIGNED_INT;
	}
}

IBO::IBO(int indicecount)
	: Format (IndexFormat::SixteenBit),
	  IndiceCount (indicecount),
	  ID(0)
{
	Build ();
}

IBO::IBO(int indicecount, IndexFormat format)
	: Format (format),
	  IndiceCount (indicecount)
{
	Build ();
}

IBO::IBO(IBO &&moveme)
	: Format(moveme.Format),
	  ID (moveme.ID),
	  IndiceCount(moveme.IndiceCount)
{
	moveme.ID = 0;
	moveme.IndiceCount = 0;
}

IBO &IBO::operator= (IBO &&moveme)
{
	if (ID != 0)
		glDeleteBuffers(1,&ID);
	ID = moveme.ID;
	moveme.ID = 0;
	Format = moveme.Format;
	return *this;
}


IBO::~IBO()
{
	glDeleteBuffers (1,&ID);
}

void IBO::Write (unsigned int *indices, int indexcount)
{
	Bind ();
	if (Format != IndexFormat::ThirtyTwoBit)
	{
		cout << "Error writing 16 bit indices to a 32 bit IBO." << endl;
		return;
	}
	glBufferSubData (GL_ELEMENT_ARRAY_BUFFER,0,indexcount * sizeof (unsigned int), static_cast <void *> (indices));
	GLErrorCheck ();
	UnBind ();
}

void IBO::Write (unsigned int *indices, int indexcount, int offset)
{
	Bind ();
	if (Format != IndexFormat::ThirtyTwoBit)
	{
		cout << "Error writing 16 bit indices to a 32 bit IBO." << endl;
		return;
	}
	glBufferSubData (GL_ELEMENT_ARRAY_BUFFER,static_cast <GLintptr> (offset * sizeof (unsigned int)),indexcount * sizeof (unsigned int), static_cast <void *> (indices));
	GLErrorCheck ();
	UnBind ();
}

void IBO::Write (unsigned short *indices, int indexcount)
{
	Bind ();
	if (Format != IndexFormat::SixteenBit)
	{
		cout << "Error writing 32 bit indices to a 16 bit IBO." << endl;
		return;
	}
	glBufferSubData (GL_ELEMENT_ARRAY_BUFFER,0,indexcount * sizeof (unsigned short), static_cast <void *> (indices));
	GLErrorCheck ();
	UnBind ();
}

void IBO::Write (unsigned short *indices, int indexcount, int offset)
{
	Bind ();
	if (Format != IndexFormat::SixteenBit)
	{
		cout << "Error writing 32 bit indices to a 16 bit IBO." << endl;
		return;
	}
	glBufferSubData (GL_ELEMENT_ARRAY_BUFFER,static_cast <GLintptr> (offset * sizeof (unsigned short)),indexcount * sizeof (unsigned short), static_cast <void *> (indices));
	GLErrorCheck ();
	UnBind ();
}

void IBO::Bind () const
{
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER,ID);
	GLErrorCheck ();
}

void IBO::UnBind () const
{
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER,0);
	GLErrorCheck ();
}

void IBO::Build ()
{
	glGenBuffers (1,&ID);
	
	Bind ();
	glBufferData (GL_ELEMENT_ARRAY_BUFFER,static_cast <GLsizeiptr> (Format.GetSize () * IndiceCount),nullptr, GL_DYNAMIC_DRAW);
	GLErrorCheck ();
	UnBind ();
}


}}