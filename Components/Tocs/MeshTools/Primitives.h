#pragma once
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/Core/LateStatic.h>
namespace Tocs {
namespace MeshTools {

class Primitives
{
	static Rendering::Mesh BuildCube();
public:
	Primitives() = delete;
	Primitives(const Primitives &) = delete;

	static FirstUseStatic<Rendering::Mesh, BuildCube> Cube;
};


}}


