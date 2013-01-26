#pragma once
#include <string>

namespace Tocs {
namespace Parallel {

class CompileResults
{
	bool Successful;
	std::string CompileErrors;
public:
	CompileResults(bool success, const std::string &errors)
		: Successful(success),
		  CompileErrors(errors)
	{
	}

	bool WasSuccessful () const { return Successful; }
	const std::string &GetErrors () { return CompileErrors; }
};

}}
