#pragma once
#include "RenderObject.h"

namespace Tocs {
namespace Rendering {

class Light : public RenderObject
{
public:
	Light (RenderSystem &system)
		: RenderObject (system)
	{}

};

}}