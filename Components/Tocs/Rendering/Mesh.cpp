#include "Mesh.h"
#include <Tocs/Graphics/GraphicsContext.h>
namespace Tocs {
namespace Rendering {

Mesh::Mesh(unsigned int vertexcount, unsigned int indexcount, Graphics::VertexFormat format)
	: VertexBuffer (vertexcount * format.SizeInBytes ()),
	  IndexBuffer (indexcount),
	  Format (format)
{
	VertexArray.Bind ();
	VertexArray.AddVBO (VertexBuffer,Format);
	VertexArray.UnBind ();
}

Mesh::Mesh (Mesh &&moveme)
	: VertexBuffer(std::move(moveme.VertexBuffer)),
	  IndexBuffer (std::move(moveme.IndexBuffer)),
	  VertexArray (std::move(moveme.VertexArray)),
	  Parts (std::move(moveme.Parts))
{
}

unsigned int Mesh::GetVerticeCount () const
{
	return VertexBuffer.GetSize () / Format.SizeInBytes ();
}
unsigned int Mesh::GetIndexCount () const
{
	return IndexBuffer.GetIndexCount ();
}

void Mesh::PushPartGeometry (unsigned int partindex)
{
	Graphics::GraphicsContext::DrawTriangles (Parts[partindex].GetOffset (), Parts[partindex].GetLength ());
}

void Mesh::Bind () const
{
	VertexArray.Bind ();
	IndexBuffer.Bind ();
}

void Mesh::UnBind () const
{
	IndexBuffer.UnBind ();
	VertexArray.UnBind ();
}

void Mesh::AddPart(const MeshPart &part)
{
	Parts.push_back(part);
}

}}