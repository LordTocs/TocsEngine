#pragma once
#include "Mesh.h"
#include <Tocs/Core/LateStatic.h>
#include "StaticGeometry.h"
namespace Tocs {
namespace Rendering {


class LightHulls
{
	LightHulls();
public:
	static LateStatic<Mesh> Cube;
	static LateStatic<Mesh> InverseCube;
	static LateStatic<StaticGeometryType> GeometryType;
};

}}

