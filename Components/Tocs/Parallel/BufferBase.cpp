#include "BufferBase.h"
#include "ErrorCheck.h"
#include <CL/cl.h>

#include <iostream>

using namespace std;

namespace Tocs {
namespace Parallel {

BufferBase::BufferBase(Context &context, BufferAccess access, unsigned int size)
	: BufferPtr (nullptr)
{
	int error;
	BufferPtr = clCreateBuffer(context.GetCLPtr (),access.GetCLEnum(),size,nullptr,&error);
	CheckError(error);
}

BufferBase::BufferBase(BufferBase&& moveme)
	: BufferPtr(moveme.BufferPtr)
{
	moveme.BufferPtr = nullptr;
}

BufferBase::~BufferBase(void)
{
	cout << this << " " << BufferPtr << endl;
	clReleaseMemObject (BufferPtr);
}

unsigned int BufferBase::LengthInBytes () const 
{
	unsigned int result;
	int error = clGetMemObjectInfo (BufferPtr,CL_MEM_SIZE,sizeof(result),&result,nullptr);
	CheckError(error);
	return result;

}

}}