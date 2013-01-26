#include "Device.h"
#include <iostream>
#include <CL/cl.h>

using namespace std;

namespace Tocs {
namespace Parallel {

Device::Device(void)
	: DevicePtr(nullptr)
{
	cl_device_id devices [10];
	unsigned int numdevices;
	clGetDeviceIDs (ParallelPlatform.GetCLPtr (),CL_DEVICE_TYPE_GPU,10,&devices[0],&numdevices);

	if (numdevices <= 0)
	{
		cout << "No Devices Found!" << endl;
	}

	DevicePtr = devices[0];
}

Device::~Device(void)
{
}

bool Device::Available () const
{
	bool result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_AVAILABLE,sizeof(bool),&result,nullptr);
	return result;
}
unsigned int Device::GetAddrBits () const
{
	unsigned int result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_ADDRESS_BITS,sizeof(unsigned int),&result,nullptr);
	return result;
}
bool Device::HasCompiler () const
{
	bool result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_COMPILER_AVAILABLE,sizeof(bool),&result,nullptr);
	return result;
}
bool Device::HasLinker () const
{
	/*bool result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_LINKER_AVAILABLE,sizeof(bool),&result,nullptr);
	return result;*/
	//1.2 feature?
	return true;
}
bool Device::LittleEndian () const
{
	bool result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_ENDIAN_LITTLE,sizeof(bool),&result,nullptr);
	return result;
}

unsigned int Device::GetMaxImageHeight () const
{
	unsigned int result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_IMAGE2D_MAX_HEIGHT,sizeof(unsigned int),&result,nullptr);
	return result;
}
unsigned int Device::GetMaxImageWidth () const
{
	unsigned int result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_IMAGE2D_MAX_WIDTH,sizeof(unsigned int),&result,nullptr);
	return result;
}
/*unsigned int Device::GetMaxBufferSize () const
{
	unsigned int result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_IMAGE_BUFFER_SIZE,sizeof(unsigned int),&result,nullptr);
	return result;
}
unsigned int Device::GetMaxArraySize () const
{
}*/
unsigned int Device::GetMaxComputeUnits () const
{
	unsigned int result;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(unsigned int),&result,nullptr);
	return result;
}

std::string Device::GetExtensions () const
{
	unsigned int len;
	clGetDeviceInfo (DevicePtr,CL_DEVICE_EXTENSIONS,0,nullptr,&len);
	std::string result;
	result.resize (len,' ');
	clGetDeviceInfo (DevicePtr,CL_DEVICE_EXTENSIONS,len,&result[0],&len);
	return result;
}

void Device::PrintInfo () const
{
	cout << "Sizeof: " << sizeof (cl_event) << endl;

	cout << "Available: " << (Available () ?  "True" : "False") << endl;
	cout << "AddrBits: " << GetAddrBits () << endl;
	cout << "HasCompiler: " << (HasCompiler () ? "True" : "False") << endl;
	cout << "Endianess: " << (LittleEndian () ? "Little" : "Big") << endl;
	cout << "MaxImageWidth: " << GetMaxImageWidth () << endl;
	cout << "MaxImageHeight: " << GetMaxImageHeight () << endl;
	cout << "MaxComputeUnits: " << GetMaxComputeUnits () << endl << endl;

	cout << "Extensions: " << GetExtensions () << endl;
}

}}