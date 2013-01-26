#include "TocsLib.h"
#include "DynamicByteBuffer.h"
#include "Numerics.h"
#include <memory>
namespace Tocs {

DynamicByteBuffer::InternalBuffer::InternalBuffer ()
	: Size (0),
	  BufferSize (16),
	  Buffer (new char [Size])
{

}

DynamicByteBuffer::InternalBuffer::InternalBuffer (const InternalBuffer &clonee)
	: Size (clonee.Size),
      BufferSize (clonee.BufferSize),
	  Buffer (new char [Size])
{
	::memcpy (Buffer,clonee.Buffer,clonee.Size);
}
DynamicByteBuffer::InternalBuffer::~InternalBuffer ()
{
	delete [] Buffer;
}
void DynamicByteBuffer::InternalBuffer::Resize (int size)
{
	if (size <= 0)
		return;

	char* NewArray = new char [size];
	//memset (NewArray,0,size);
			
	if (Buffer != nullptr)
	{
		std::memcpy (NewArray, Buffer, (size < Size ? size : Size));
	}

	BufferSize = size;

	if (Size > BufferSize)
		BufferSize = Size;
	
	delete [] Buffer;

	Buffer = NewArray;
}

void DynamicByteBuffer::InternalBuffer::MakeBigEnough (int size)
{
	if (size > Size)
	{
		Resize (GetLargerPowerOfTwo (size));
	}
}

void DynamicByteBuffer::InternalBuffer::Write (int location, char *data, int size)
{
	if (location + size > BufferSize)
	{
		MakeBigEnough (location + size);
	}
	memcpy (&Buffer[location],data,size);
	if (location + size > Size)
	{
		Size = location + size;
	}
}

DynamicByteBuffer::DynamicByteBuffer()
	: Buffer (new InternalBuffer ())
{

}

void DynamicByteBuffer::Write (int location, char *data, int size)
{
	Buffer.PrepareWrite ();
	Buffer.GetPayload ().Write (location,data,size);
}
void DynamicByteBuffer::Read  (int location, char *data, int size)
{
	::memcpy (data,&Buffer.GetPayload ().Buffer[location],size);
}
bool DynamicByteBuffer::CanWrite (int location, int size) const
{
	return location >= 0;
}
bool DynamicByteBuffer::CanRead  (int location, int size) const
{
	return location >= 0 && location + size <= Buffer.GetPayload ().Size;
}

}