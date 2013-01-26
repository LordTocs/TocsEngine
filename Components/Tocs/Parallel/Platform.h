#pragma once
#include <string>

struct _cl_platform_id;

namespace Tocs {
namespace Parallel {

class Platform
{
	_cl_platform_id *PlatformPtr;
public:
	Platform (); //Finds "best" platform
	Platform(_cl_platform_id *platform)
		: PlatformPtr (platform)
	{}
	~Platform();

	std::string GetName () const;
	std::string GetVersionString () const;
	std::string GetVendor () const;

	_cl_platform_id *GetCLPtr ()
	{ return PlatformPtr; }
};

}}
