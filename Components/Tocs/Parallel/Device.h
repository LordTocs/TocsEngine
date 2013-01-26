#pragma once
#include "Platform.h"
#include <string>


struct _cl_device_id;
namespace Tocs {
namespace Parallel {

class Device
{
	Platform ParallelPlatform;
	_cl_device_id *DevicePtr;

	Device(const Device &);
public:
	Device();
	Device(_cl_device_id *device)
		: DevicePtr(device) {}
	~Device();

	_cl_device_id *GetCLPtr ()
	{ return DevicePtr; }

	bool Available () const;
	unsigned int GetAddrBits () const;
	bool HasCompiler () const;
	bool HasLinker () const;
	bool LittleEndian () const;

	Platform &GetPlatform () { return ParallelPlatform; }

	unsigned int GetMaxImageHeight () const;
	unsigned int GetMaxImageWidth () const;
	//unsigned int GetMaxBufferSize () const;
	//unsigned int GetMaxArraySize () const;

	unsigned int GetMaxComputeUnits () const;
	std::string GetExtensions () const;

	void PrintInfo () const;



};

}}