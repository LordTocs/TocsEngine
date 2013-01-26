#pragma once

namespace Tocs {
namespace Parallel {

class BufferAccess
{
	enum InternalFormat
	{
		read,
		write,
		readwrite
	};
	InternalFormat Internal;

	BufferAccess (InternalFormat format)
		: Internal (format) {}

public:
	const static BufferAccess Read;
	const static BufferAccess Write;
	const static BufferAccess ReadWrite;

	bool operator ==  (const BufferAccess &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const BufferAccess &op2) const {return Internal != op2.Internal;}
	bool operator < (const BufferAccess &op2) const { return Internal < op2.Internal; }

	int GetCLEnum () const;
};

}}
