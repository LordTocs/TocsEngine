#pragma once
#include "Pipe.h"
#include <string>
namespace Tocs {
namespace Rendering {

class Pipeline
{

public:
	Pipe &GetPipeByName (const std::string &name);

};

}}