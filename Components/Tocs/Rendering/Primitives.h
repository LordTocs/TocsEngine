#pragma once
#include "Mesh.h"
#include <Tocs/Core/LateStatic.h>
namespace Tocs {
namespace Rendering {

class Primitives
{
	Primitives();
	Primitives(const Primitives &);
public:
	static LateStatic<Mesh> Cube;
};

}}