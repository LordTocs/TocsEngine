#include "Enums.h"
#include <CL/cl.h>
namespace Tocs {
namespace Parallel {

const BufferAccess BufferAccess::Read(read);
const BufferAccess BufferAccess::Write(write);
const BufferAccess BufferAccess::ReadWrite(readwrite);

int BufferAccess::GetCLEnum () const
{
	switch (Internal)
	{
	case read:
		return CL_MEM_READ_ONLY;
	case write:
		return CL_MEM_WRITE_ONLY;
	case readwrite:
		return CL_MEM_READ_WRITE;
	}
}

}}
