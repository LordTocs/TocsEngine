#include "Buffer.h"
#include "GLHeader.h"
#include <cmath>
#include <algorithm>

namespace Tocs {
namespace Graphics {

const BufferTarget BufferTarget::Vertex(GL_ARRAY_BUFFER);
const BufferTarget BufferTarget::Index(GL_ELEMENT_ARRAY_BUFFER);
const BufferTarget BufferTarget::Texture(GL_TEXTURE_BUFFER);
const BufferTarget BufferTarget::Uniform(GL_UNIFORM_BUFFER);
const BufferTarget BufferTarget::TransformFeedback(GL_TRANSFORM_FEEDBACK_BUFFER);
const BufferTarget BufferTarget::Read(GL_COPY_READ_BUFFER);
const BufferTarget BufferTarget::Write(GL_COPY_WRITE_BUFFER);
const BufferTarget BufferTarget::AtomicCounter(GL_ATOMIC_COUNTER_BUFFER);
const BufferTarget BufferTarget::ShaderStorage(GL_SHADER_STORAGE_BUFFER);

unsigned int BufferTarget::GLValue () const
{
	return Internal;
}

BufferBase::BufferBase(unsigned int bytes)
	: ID (0)
{
	glGenBuffers (1,&ID);
	GLErrorCheck();
	Build(bytes);
}

BufferBase::BufferBase(BufferBase &&moveme)
	: ID (moveme.ID)
{
	moveme.ID = 0;

#if _DEBUG
	CurrentBinding = moveme.CurrentBinding;
#endif
}

BufferBase::~BufferBase()
{
	glDeleteBuffers (1,&ID);
	GLErrorCheck();
}

BufferBase &BufferBase::operator=(BufferBase &&moveme)
{
	ID = moveme.ID;
	moveme.ID = 0;
#if _DEBUG
	CurrentBinding = moveme.CurrentBinding;
#endif
	return *this;
}

void BufferBase::Bind (BufferTarget target) const
{
#ifdef _DEBUG
	const_cast<Binding &> (CurrentBinding).Base = -1;
	const_cast<Binding &> (CurrentBinding).Target = target.GLValue ();
#endif
	glBindBuffer (target.GLValue(), ID);
	GLErrorCheck();
}

void BufferBase::BindTo (BufferTarget target, unsigned int index) const
{
#ifdef _DEBUG
	const_cast<Binding &> (CurrentBinding).Base = index;
	const_cast<Binding &> (CurrentBinding).Target = target.GLValue ();
#endif
	glBindBufferBase (target.GLValue(),index,ID);
	GLErrorCheck();
}

void BufferBase::BindToRange (BufferTarget target, unsigned int index, unsigned int offset, unsigned int size) const
{
#ifdef _DEBUG
	const_cast<Binding &> (CurrentBinding).Base = index;
	const_cast<Binding &> (CurrentBinding).Target = target.GLValue ();
#endif
	glBindBufferRange (target.GLValue(),index,ID,offset,size);
	GLErrorCheck();
}

void BufferBase::UnBind () const
{
#ifdef _DEBUG
	if (CurrentBinding.Base == -1)
	{
		glBindBuffer (CurrentBinding.Target, 0);
		GLErrorCheck();
	}
	else
	{
		glBindBufferBase (CurrentBinding.Target,CurrentBinding.Base,0);
		GLErrorCheck ();
	}
	const_cast<Binding &> (CurrentBinding).Base = -1;
	const_cast<Binding &> (CurrentBinding).Target = -1;
#endif
}


void BufferBase::Write (const void *bytes, unsigned int size)
{
	Write (bytes,0,size);
}
void BufferBase::Write (const void *bytes, unsigned int offset, unsigned int size)
{
	Bind (BufferTarget::Write);

	glBufferSubData (BufferTarget::Write.GLValue(),offset,size,bytes);
	GLErrorCheck ();

	UnBind ();
}

void BufferBase::Read (void *bytes, unsigned int size) const
{
	Read (bytes,0,size);
}

void BufferBase::Read (void *bytes, unsigned int offset, unsigned int size) const
{
	Bind (BufferTarget::Read);

	glGetBufferSubData (BufferTarget::Read.GLValue (), offset, size, bytes);
	GLErrorCheck ();

	UnBind ();
}

void BufferBase::Resize (unsigned int bytes)
{
	unsigned int newid;
	//Name the buffer
	glGenBuffers (1,&newid);
	GLErrorCheck ();
	
	//Bind the write
	glBindBuffer (BufferTarget::Write.GLValue (),newid);
	GLErrorCheck ();
	
	//Allocate the new buffer
	glBufferData (BufferTarget::Write.GLValue (), bytes, nullptr, GL_DYNAMIC_DRAW);
	GLErrorCheck ();

	//Bind the read
	Bind(BufferTarget::Read);

	//Copy
	glCopyBufferSubData (BufferTarget::Read.GLValue (), BufferTarget::Write.GLValue (),0,0,SizeInBytes ());
	GLErrorCheck ();

	//Unbind the read
	UnBind ();

#ifdef _DEBUG
	//Unbind the write
	glBindBuffer (BufferTarget::Write.GLValue (),0);
	GLErrorCheck ();
#endif
	//Delete the old
	glDeleteBuffers (1,&ID);
	GLErrorCheck();

	//Use the new
	ID = newid;
}

void BufferBase::Build (unsigned int bytes)
{
	Bind (BufferTarget::Write);
	glBufferData (BufferTarget::Write.GLValue(), bytes, nullptr, GL_DYNAMIC_DRAW);
	GLErrorCheck ();
	UnBind ();
}

void BufferBase::CopyTo (BufferBase &other) const
{
	Bind (BufferTarget::Read);
	other.Bind (BufferTarget::Write);

	unsigned int maxlen = std::max(SizeInBytes(),other.SizeInBytes());

	glCopyBufferSubData (BufferTarget::Read.GLValue (), BufferTarget::Write.GLValue (),0,0,maxlen);
	GLErrorCheck ();

	UnBind ();
	other.UnBind();
}

unsigned int BufferBase::SizeInBytes () const
{
	Bind (BufferTarget::Read);

	int size = 0;
	glGetBufferParameteriv (BufferTarget::Read.GLValue (),GL_BUFFER_SIZE,&size);
	GLErrorCheck ();

	UnBind ();

	return size;
}

void *BufferBase::Map()
{
	Bind(BufferTarget::Write);
	void *result = glMapBuffer(BufferTarget::Write.GLValue(), GL_READ_WRITE);
	GLErrorCheck();
	return result;
}

void BufferBase::UnMap()
{
	glUnmapBuffer(BufferTarget::Write.GLValue());
	GLErrorCheck();
}

}}