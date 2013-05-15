#pragma once
#include "Mesh.h"
#include <Tocs/Core/LateStatic.h>
#include "StaticGeometry.h"
namespace Tocs {
namespace Rendering {


class LightHulls
{
	LightHulls();
	static Mesh BuildCube ();
	static Mesh BuildInverseCube ();
	static StaticGeometryType BuildGeometryType();
public:
	static FirstUseStatic<Mesh,&BuildCube> Cube;
	static FirstUseStatic<Mesh,&BuildInverseCube> InverseCube;
	static FirstUseStatic<StaticGeometryType,&BuildGeometryType> GeometryType;
};

}}

