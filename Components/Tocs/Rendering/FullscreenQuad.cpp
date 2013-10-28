#include "FullscreenQuad.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/GraphicsContext.h>
namespace Tocs {
namespace Rendering {

FullscreenQuad::FullscreenQuad()
	: VertexBuffer (4 * sizeof (PositionTextureNormal)),
	  IndexBuffer (6)
{
	Vertices[0](Math::Vector3(-1,-1,0),Math::Vector2(0,0));
	Vertices[1](Math::Vector3( 1,-1,0),Math::Vector2(1,0));
	Vertices[2](Math::Vector3(-1, 1,0),Math::Vector2(0,1));
	Vertices[3](Math::Vector3( 1, 1,0),Math::Vector2(1,1));

	VertexBuffer.Write(Vertices,4,0);

	VertexArrayBuffer.Bind();
	VertexArrayBuffer.AddVBO(VertexBuffer,PositionTextureNormal::Format.Get());
	VertexArrayBuffer.UnBind();

	unsigned short indices [6] = {0,1,2, 1,2,3};
	IndexBuffer.Write (indices,6,0);

	VertexBuffer.Write(Vertices,4,0);
}

void FullscreenQuad::SetCornerNormals(const Math::Vector3 &tl, const Math::Vector3 &tr, const Math::Vector3 &bl, const Math::Vector3 &br)
{
	Vertices[0].Normal = tl;
	Vertices[1].Normal = tr;
	Vertices[2].Normal = bl;
	Vertices[3].Normal = br;
	VertexBuffer.Write(Vertices,4,0);
}

void FullscreenQuad::PushGeometry (Graphics::GraphicsContext &context) const
{
	VertexArrayBuffer.Bind();
	IndexBuffer.Bind();
	context.DrawTriangles(0,3);
	IndexBuffer.UnBind ();
	VertexArrayBuffer.UnBind();
}

}}