#include "Program.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <CL\cl.h>

using namespace std;

namespace Tocs {
namespace Parallel {

Program::~Program(void)
{
	if (ProgramPtr != nullptr)
		clReleaseProgram (ProgramPtr);
}

CompileResults Program::Compile (const std::string &source)
{
	unsigned int length = source.length ();
	const char *sourcecstr = source.c_str();
	int error;
	ProgramPtr = clCreateProgramWithSource (_Context.GetCLPtr (),1,&sourcecstr, &length,&error);
	clBuildProgram (ProgramPtr,0,nullptr,nullptr,nullptr,nullptr);

	
	
	unsigned int loglength;
	int status;
	clGetProgramBuildInfo (ProgramPtr,_Context.GetDevice().GetCLPtr(),CL_PROGRAM_BUILD_STATUS,sizeof(int),&status,nullptr);
	clGetProgramBuildInfo (ProgramPtr,_Context.GetDevice().GetCLPtr(),CL_PROGRAM_BUILD_LOG,0,nullptr,&loglength);

	unique_ptr<char[]> log (new char [loglength] ());

	clGetProgramBuildInfo (ProgramPtr,_Context.GetDevice().GetCLPtr(),CL_PROGRAM_BUILD_LOG,loglength,log.get(),&loglength);


	return CompileResults (status == CL_BUILD_SUCCESS,std::string(&log[0]));
}

CompileResults Program::CompileFromFile (const std::string &filename)
{
	ifstream file (filename);
	if (!file.is_open() || !file.good())
	{
		stringstream errstr;
		errstr << "Could not open file: " << filename << endl;

		return CompileResults (false,errstr.str ());
	}
	string source (istreambuf_iterator<char>(file),(istreambuf_iterator<char> ()));
	return Compile (source);
}


KernelBase Program::GetKernel (const std::string &name)
{
	return KernelBase (*this,name);
}

}}