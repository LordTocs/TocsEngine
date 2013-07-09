#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Rendering/StaticGeometry.h>
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/Math/Vector3.h>
#include <Tocs/Rendering/Geometry.h>
#include <Tocs/Graphics/UniformMap.h>

namespace Tocs {
namespace MeshTools {

class LatticeGeometry : public Rendering::Geometry
{
	Math::Vector3 LatticePoints[8];
	Graphics::UniformMap Uniforms;
	Asset<Rendering::Mesh> MeshBuffer;
	Asset<Rendering::StaticGeometryType> Type;
public:
	LatticeGeometry (const Asset<Rendering::Mesh> &meshbuffer);

	const Rendering::GeometryType &GetType () const { return Type.Get(); }

	void PassToShader (Graphics::Shader &shader) const;
	
	int PartCount () const 
	{ return MeshBuffer.Get().PartCount(); }

	void PushGeometry (unsigned int part) const
	{ 
		MeshBuffer.Get().Bind ();
		MeshBuffer.Get().PushPartGeometry (part);
		MeshBuffer.Get().UnBind ();
	}
};

}}

