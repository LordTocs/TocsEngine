#pragma once
#include <Tocs/Core/Asset.h>
#include "Geometry.h"
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/UniformMap.h>
#include <vector>
#include "Mesh.h"

namespace Tocs {
namespace Rendering {

class StaticGeometryType : public GeometryType
{
	std::vector<Asset<Graphics::ShaderCode>> Shaders;
public:
	void ImportShader (Asset<Graphics::ShaderCode> shader);
	void AddShaders (Graphics::Shader &targetshader) const;

	static StaticGeometryType LoadFromFile (const std::string &filename);
};

class StaticGeometry : public Geometry
{
	Graphics::UniformMap Uniforms;
	const StaticGeometryType &Type;
	const Mesh *MeshBuffer;
public:
	StaticGeometry(const Mesh &mesh, const StaticGeometryType &type)
		: MeshBuffer(&mesh),
		  Type(type) //Add type deduction from VertexFormat.
	{}

	const GeometryType &GetType () const { return Type; }

	Graphics::UniformMap::UniformValue &operator[] (const std::string &name)
	{ return Uniforms[name]; }

	void PassToShader (Graphics::Shader &shader) const
	{ Uniforms.PassToShader(shader); }

	int PartCount () const 
	{ return MeshBuffer->PartCount(); }

	void PushGeometry (unsigned int part) const
	{ 
		MeshBuffer->Bind ();
		MeshBuffer->PushPartGeometry (part);
		MeshBuffer->UnBind ();
	}
};

}}