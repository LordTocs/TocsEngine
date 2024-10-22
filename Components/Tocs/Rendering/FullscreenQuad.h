#pragma once
#include <Tocs/Graphics/GraphicsContext.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Math/Vector.h>
#include "Vertices.h"
//#include "StaticGeometry.h"
namespace Tocs {
namespace Rendering {


class FullscreenQuad
{
	PositionTextureNormal Vertices  [4];
	Graphics::Buffer<PositionTextureNormal> VertexBuffer;
	Graphics::Buffer<unsigned int> IndexBuffer;
	Graphics::VAO VertexArrayBuffer;
public:
	FullscreenQuad();

	void SetCornerNormals (const Math::Vector3 &tl, const Math::Vector3 &tr, const Math::Vector3 &bl, const Math::Vector3 &br);
	void PushGeometry (Graphics::GraphicsContext &context) const;

	//Geometry overrides.

	int PartCount () const 
	{ return 1; }
};

}}