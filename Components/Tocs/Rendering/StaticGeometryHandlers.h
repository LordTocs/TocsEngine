#pragma once
#include "Vertices.h"
#include "GeometryHandler.h"
namespace Tocs {
namespace Rendering {

template <class T>
GeometryHandler& GetStaticGeometryHandler ();

template <>
GeometryHandler& GetStaticGeometryHandler <PositionTextureNormal> ()
{
	static Asset<GeometryHandler> Handler = Asset<GeometryHandler>::Load("PositionTextureNormal.vert");
	return Handler.Get ();
}



}}