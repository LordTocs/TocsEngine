#pragma once
#include "KernelBase.h"

#include "Context.h"
#include "CompileResults.h"


#include <string>
struct _cl_program;

namespace Tocs {
namespace Parallel {

class Program
{
	_cl_program *ProgramPtr;
	Context &_Context;
	Program (const Program &); //No Copying
public:
	Program(Context &context)
		: ProgramPtr(nullptr),
		  _Context(context)
	{
	}

	~Program();

	_cl_program *GetCLPtr () { return ProgramPtr; }

	CompileResults Compile (const std::string &source);
	CompileResults CompileFromFile (const std::string &filename);

	KernelBase GetKernel (const std::string &name);
	
};

}}