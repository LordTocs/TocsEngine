#include "Platform.h"
#include <CL/cl.h>
#include <iostream>
using namespace std;

namespace Tocs {
namespace Parallel {

Platform::Platform()
	: PlatformPtr (nullptr)
{
	cl_platform_id Platforms [5];
	unsigned int NumRet;
	clGetPlatformIDs (5,&Platforms[0],&NumRet);

	if (NumRet < 0)
	{
		cout << "No Devices Found!" << endl;
	}

	PlatformPtr = Platforms[NumRet - 1];

	cout << "Platform: " << endl;
	cout << "Name: " << GetName () << endl;
	cout << "Version: " << GetVersionString () << endl;
	cout << "Vendor: " << GetVendor () << endl << endl;

	/*cout << NumRet << " OpenCL Platforms Found." << endl;
	for (int i = 0; i < NumRet; ++i)
	{
		Platform testp (Platforms[i]);
		cout << "Platform " << i << ": " << endl;
		cout << "Name: " << testp.GetName () << endl;
		cout << "Version: " << testp.GetVersionString () << endl;
		cout << "Vendor: " << testp.GetVendor () << endl << endl;

		
	}*/
}

Platform::~Platform(void)
{
}

std::string Platform::GetName () const
{
	char str [200];
	size_t outsize;
	clGetPlatformInfo (PlatformPtr,CL_PLATFORM_NAME,200,&str[0],&outsize);
	return string (&str[0]);
}

std::string Platform::GetVersionString () const
{
	char str [200];
	size_t outsize;
	clGetPlatformInfo (PlatformPtr,CL_PLATFORM_VERSION,200,&str[0],&outsize);
	return string (&str[0]);
}

std::string Platform::GetVendor () const
{
	char str [200];
	size_t outsize;
	clGetPlatformInfo (PlatformPtr,CL_PLATFORM_VENDOR,200,&str[0],&outsize);
	return string (&str[0]);
}

}}