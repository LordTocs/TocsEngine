#include "KernelBase.h"
#include "Program.h"
#include "ErrorCheck.h"
#include <CL/cl.h>
#include <iostream>

using namespace std;

namespace Tocs {
namespace Parallel {

KernelBase::KernelBase(const KernelBase &copyme)
	: KernelPtr(copyme.KernelPtr)
{
	clRetainKernel (KernelPtr);
}

KernelBase::KernelBase(Program &program, const std::string &name)
	: KernelPtr (nullptr)
{
	int error;
	KernelPtr = clCreateKernel (program.GetCLPtr (),name.c_str(),&error);

	if (CheckError(error))
	{
		cout << "Error getting kernel: " << name << endl;
	}
}


KernelBase::~KernelBase()
{
	clReleaseKernel (KernelPtr);
}

KernelBase &KernelBase::operator= (const KernelBase &copyme)
{
	if (KernelPtr != nullptr)
	{
		clReleaseKernel (KernelPtr);
	}
	KernelPtr = copyme.KernelPtr;
	clRetainKernel (KernelPtr);
	return *this;
}

void KernelBase::SetArgInternal (int arg, unsigned int size, const void *value)
{
	//cout << "Setting arg internal: " << arg << " " << size << " " << value << endl;
	int error = clSetKernelArg (KernelPtr,arg,size,value);

	if (CheckError(error))
	{
		cout << "Error setting argument " << arg << " of " << GetName () << endl;
	}
}


std::string KernelBase::GetName () const
{
	unsigned int len;
	clGetKernelInfo (KernelPtr,CL_KERNEL_FUNCTION_NAME,0,nullptr,&len);
	std::string result;
	result.resize (len,' ');
	clGetKernelInfo (KernelPtr,CL_KERNEL_FUNCTION_NAME,len,&result[0],&len);
	return result;
}

}}