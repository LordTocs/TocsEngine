#include "LatticeGeometry.h"
#include <Tocs/Parallel/Kernel.h>
namespace Tocs {
namespace MeshTools {

	/*
	LatticeGeometry::LatticeGeometry(const Asset<Rendering::Mesh> &meshbuffer)
		: MeshBuffer(meshbuffer),
		  Type(Asset<Rendering::StaticGeometryType>::Load("Lattice.vert"))
	{
	}

	void LatticeGeometry::PassToShader (Graphics::Shader &shader) const
	{
		shader["Lattice"] = LatticePoints;
		//shader["BoundsCenter"] = MeshBuffer.Get().ge();
		Uniforms.PassToShader(shader); 
	}
	*/

}}