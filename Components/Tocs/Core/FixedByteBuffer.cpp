#include "TocsLib.h"
#include "FixedByteBuffer.h"
#include <memory>

using namespace std;
using namespace Tocs;

FixedByteBuffer::InternalBuffer::InternalBuffer (int size)
	: Size (size),
	  Buffer(new char [Size])
{
	
}

FixedByteBuffer::InternalBuffer::~InternalBuffer ()
{
	if (Buffer != nullptr)
		delete [] Buffer;
}

FixedByteBuffer::InternalBuffer::InternalBuffer (InternalBuffer &clonee)
	: Size (clonee.Size),
	  Buffer(new char [Size])
{
	::memcpy (Buffer,clonee.Buffer,Size);
}

FixedByteBuffer::InternalBuffer::InternalBuffer ()
	: Size (0),
	  Buffer (nullptr)
{
}
FixedByteBuffer::FixedByteBuffer(int Size)
	: Buffer (new InternalBuffer (Size))
{
}
FixedByteBuffer::~FixedByteBuffer(void)
{
}

void FixedByteBuffer::Write (int location, char *data, int size)
{
	Buffer.PrepareWrite ();
	::memcpy (&Buffer.GetPayload ().Buffer[location],data,size);
}
void FixedByteBuffer::Read  (int location, char *data, int size)
{
	::memcpy (data,&Buffer.GetPayload ().Buffer[location],size);
}
bool FixedByteBuffer::CanWrite (int location, int size)
{
	return location >= 0 && location + size <= Buffer.GetPayload ().Size;
}
bool FixedByteBuffer::CanRead  (int location, int size)
{
	return location >= 0 && location + size <= Buffer.GetPayload ().Size;
}