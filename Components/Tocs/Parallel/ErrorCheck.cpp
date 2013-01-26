#include "ErrorCheck.h"
#include <iostream>
#include <string>
#include <CL/cl.h>

namespace Tocs {
namespace Parallel {

static std::string GetErrorString (int error)
{
	switch(error)
	{
		GenErrorCase(CL_SUCCESS)
		GenErrorCase(CL_DEVICE_NOT_FOUND)
		GenErrorCase(CL_DEVICE_NOT_AVAILABLE)
		GenErrorCase(CL_COMPILER_NOT_AVAILABLE)
		GenErrorCase(CL_MEM_OBJECT_ALLOCATION_FAILURE)
		GenErrorCase(CL_OUT_OF_RESOURCES)
		GenErrorCase(CL_OUT_OF_HOST_MEMORY)
		GenErrorCase(CL_PROFILING_INFO_NOT_AVAILABLE)
		GenErrorCase(CL_MEM_COPY_OVERLAP)
		GenErrorCase(CL_IMAGE_FORMAT_MISMATCH)
		GenErrorCase(CL_IMAGE_FORMAT_NOT_SUPPORTED)
		GenErrorCase(CL_BUILD_PROGRAM_FAILURE)
		GenErrorCase(CL_MAP_FAILURE)
		GenErrorCase(CL_MISALIGNED_SUB_BUFFER_OFFSET)
		GenErrorCase(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST)
		GenErrorCase(CL_INVALID_VALUE)
		GenErrorCase(CL_INVALID_DEVICE_TYPE)
		GenErrorCase(CL_INVALID_PLATFORM)
		GenErrorCase(CL_INVALID_DEVICE)
		GenErrorCase(CL_INVALID_CONTEXT)
		GenErrorCase(CL_INVALID_QUEUE_PROPERTIES)
		GenErrorCase(CL_INVALID_COMMAND_QUEUE)
		GenErrorCase(CL_INVALID_HOST_PTR)
		GenErrorCase(CL_INVALID_MEM_OBJECT)
		GenErrorCase(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR)
		GenErrorCase(CL_INVALID_IMAGE_SIZE)
		GenErrorCase(CL_INVALID_SAMPLER)
		GenErrorCase(CL_INVALID_BINARY)
		GenErrorCase(CL_INVALID_BUILD_OPTIONS)
		GenErrorCase(CL_INVALID_PROGRAM)
		GenErrorCase(CL_INVALID_PROGRAM_EXECUTABLE)
		GenErrorCase(CL_INVALID_KERNEL_NAME)
		GenErrorCase(CL_INVALID_KERNEL_DEFINITION)
		GenErrorCase(CL_INVALID_KERNEL)
		GenErrorCase(CL_INVALID_ARG_INDEX)
		GenErrorCase(CL_INVALID_ARG_VALUE)
		GenErrorCase(CL_INVALID_ARG_SIZE)
		GenErrorCase(CL_INVALID_KERNEL_ARGS)
		GenErrorCase(CL_INVALID_WORK_DIMENSION)
		GenErrorCase(CL_INVALID_WORK_GROUP_SIZE)
		GenErrorCase(CL_INVALID_WORK_ITEM_SIZE)
		GenErrorCase(CL_INVALID_GLOBAL_OFFSET)
		GenErrorCase(CL_INVALID_EVENT_WAIT_LIST)
		GenErrorCase(CL_INVALID_EVENT)
		GenErrorCase(CL_INVALID_OPERATION)
		GenErrorCase(CL_INVALID_GL_OBJECT)
		GenErrorCase(CL_INVALID_BUFFER_SIZE)
		GenErrorCase(CL_INVALID_MIP_LEVEL)
		GenErrorCase(CL_INVALID_GLOBAL_WORK_SIZE)
		GenErrorCase(CL_INVALID_PROPERTY)
	}
	return "Unknown Error";
}

bool CheckError (int error)
{
	if (error != CL_SUCCESS)
	{
		std::cout << GetErrorString (error) << std::endl;
		return true;
	}
	return false;
}

}}