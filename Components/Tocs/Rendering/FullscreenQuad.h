#pragma once
#include <Tocs/Graphics/VBO.h>
#include <Tocs/Graphics/IBO.h>
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Math/Vector3.h>
#include "Vertices.h"
#include "StaticGeometry.h"
namespace Tocs {
namespace Rendering {

class FullscreenQuad : public Rendering::Geometry
{
	PositionTextureNormal Vertices  [4];
	Graphics::VBO VertexBuffer;
	Graphics::IBO IndexBuffer;
	Graphics::VAO VertexArrayBuffer;
	Asset<StaticGeometryType> Type;
public:
	FullscreenQuad();

	void SetCornerNormals (const Math::Vector3 &tl, const Math::Vector3 &tr, const Math::Vector3 &bl, const Math::Vector3 &br);
	void PushGeometry () const;

	//Geometry overrides.

	void PushGeometry (unsigned int part) const
	{ PushGeometry (); }

	int PartCount () const 
	{ return 1; }

	void Prep (const Camera &cam) const {}

	void PassToShader (Graphics::Shader &shader) const {}
	
	const GeometryType &GetType () const { return Type.Get(); }
};

}}