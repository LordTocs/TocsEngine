#pragma once
#include "TocsAPI.h"
#include "CopyOnWriteBuffer.h"
#include "DataSource.h"

namespace Tocs {

TocsAPI
class DynamicByteBuffer : public DataSource
{
	class InternalBuffer
	{
	public:
		int BufferSize;
		int Size;
		char *Buffer;
		InternalBuffer ();
		InternalBuffer (const InternalBuffer &clonee);
		~InternalBuffer ();
		void Resize (int size);
		void MakeBigEnough (int size);
		void Write (int location, char *data, int size);
	};
	CopyOnWriteBuffer <InternalBuffer> Buffer;
public:
	DynamicByteBuffer();
	
	void Write (int location, char *data, int size);
	void Read  (int location, char *data, int size);
	bool CanWrite (int location, int size) const;
	bool CanRead  (int location, int size) const;

	const char *GetData () const
	{
		return Buffer.GetPayload ().Buffer;
	}

	int Length () const
	{
		return Buffer.GetPayload ().Size;
	}
};

}