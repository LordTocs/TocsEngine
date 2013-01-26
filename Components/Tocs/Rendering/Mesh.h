#pragma once
#include <vector>
#include <Tocs/Graphics/VBO.h>
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Graphics/IBO.h>
#include "MeshPart.h"
#include "GeometryHandler.h"

namespace Tocs {
namespace Rendering {

class Mesh
{
	Graphics::VBO VertexBuffer;
	Graphics::IBO IndexBuffer;
	Graphics::VAO VertexArray;
	Graphics::VertexFormat Format;
	std::vector <MeshPart> Parts;
public:
	Mesh(unsigned int vertexcount, unsigned int indexcount, Graphics::VertexFormat format);
	Mesh(Mesh &&moveme);

	Graphics::VBO &GetVertexBuffer () { return VertexBuffer; }
	Graphics::IBO &GetIndexBuffer () { return IndexBuffer; }

	unsigned int GetVerticeCount () const;
	unsigned int GetIndexCount () const;

	unsigned int PartCount () const { return Parts.size (); }

	void PushPartGeometry (unsigned int partindex); 

	void Bind () const;
	void UnBind () const;

	void AddPart (const MeshPart &part);
};

}}

