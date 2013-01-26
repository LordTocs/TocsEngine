#pragma once
#include "TocsAPI.h"
#include "CopyOnWriteBuffer.h"
#include "DataSource.h"

namespace Tocs {


class TocsAPI FixedByteBuffer : public DataSource
{
	class TocsAPI InternalBuffer
	{
	public:
		int Size;
		char *Buffer;
		InternalBuffer ();
		InternalBuffer (int size);
		InternalBuffer (InternalBuffer &clonee);
		~InternalBuffer ();
	};
	CopyOnWriteBuffer <InternalBuffer> Buffer;
public:
	explicit FixedByteBuffer(int Size);
	~FixedByteBuffer(void);

	void Write (int location, char *data, int size);
	void Read  (int location, char *data, int size);
	bool CanWrite (int location, int size);
	bool CanRead  (int location, int size);
};

}