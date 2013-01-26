#pragma once
#include "Context.h"
#include "Enums.h"
#include <type_traits>
struct _cl_mem;

namespace Tocs {
namespace Parallel {

class BufferBase
{
	_cl_mem *BufferPtr;
	explicit BufferBase(const BufferBase &copyme); //Expensive buffer copy! (Hence explicit)
public:
	BufferBase(Context &context, BufferAccess access, unsigned int size_in_bytes);
	BufferBase(BufferBase &&moveme);
	~BufferBase();

	_cl_mem *GetCLPtr () const { return BufferPtr; }

	unsigned int LengthInBytes () const;
};



}}