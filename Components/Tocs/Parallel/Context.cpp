#include "Context.h"
#include "ErrorCheck.h"
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <Tocs/Graphics/GraphicsContext.h>
#include <iostream>

using namespace std;

namespace Tocs {
namespace Parallel {

Context::Context(Device &device)
	: ContextPtr(nullptr),
	  _Device(device)
{
	int error;
	cl_device_id id = device.GetCLPtr();
	ContextPtr = clCreateContext (nullptr,1,&id,nullptr,nullptr,&error);
	if (CheckError(error))
	{
		cout << "Error creating context" << endl;
	}
}

Context::Context(Device &device, Graphics::GraphicsContext &context)
	: ContextPtr(nullptr),
	  _Device(device)
{
	int error;
	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties) context.GetContext (), 
		CL_WGL_HDC_KHR, (cl_context_properties)    context.GetTarget().GetHDC (), 
	    CL_CONTEXT_PLATFORM, (cl_context_properties) device.GetPlatform().GetCLPtr (), 
	   0};
	cl_device_id id = device.GetCLPtr();
	ContextPtr = clCreateContext (properties,1,&id,nullptr,nullptr,&error);
	if (CheckError(error))
	{
		cout << "Error creating context" << endl;
	}
}
Context::~Context(void)
{
	clReleaseContext (ContextPtr);
}

}}