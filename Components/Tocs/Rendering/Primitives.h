#pragma once
#include "Mesh.h"
#include <Tocs/Core/LateStatic.h>
namespace Tocs {
namespace Rendering {

class Primitives
{
	Primitives();
	Primitives(const Primitives &);
	static Mesh BuildCube ();
public:
	static FirstUseStatic<Mesh, &BuildCube> Cube;
};

}}