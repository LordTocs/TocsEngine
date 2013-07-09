#pragma once
#include <vector>
#include <Tocs/Graphics/VBO.h>
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Graphics/IBO.h>
#include <Tocs/Math/BoundingBox.h>
#include "MeshPart.h"


namespace Tocs {
namespace Rendering {

class Mesh
{
	Graphics::VBO VertexBuffer;
	Graphics::IBO IndexBuffer;
	Graphics::VAO VertexArray;
	Graphics::VertexFormat Format;
	std::vector <MeshPart> Parts;
	Math::BoundingBox BoundingBox;
public:
	Mesh(unsigned int vertexcount, unsigned int indexcount, const Graphics::VertexFormat &format);
	Mesh(unsigned int vertexcount, unsigned int indexcount, const Graphics::VertexFormat &format, const Graphics::IndexFormat &iformat);
	Mesh(Mesh &&moveme);

	const Graphics::VBO &GetVertexBuffer () const { return VertexBuffer; }
	const Graphics::IBO &GetIndexBuffer () const { return IndexBuffer; }

	unsigned int GetVerticeCount () const;
	unsigned int GetIndexCount () const;

	unsigned int PartCount () const { return Parts.size (); }

	void PushPartGeometry (unsigned int partindex) const; 

	const Math::BoundingBox &GetBounds () const { return BoundingBox; }

	void Bind () const;
	void UnBind () const;

	void AddPart (const MeshPart &part);

	Mesh &operator= (Mesh &&moveme);

	template <class T>
	void WriteVertices (T *data, int count) { VertexBuffer.Write(data,count); BoundingBox = Math::BoundingBox::Fit(data,count); }

	void WriteIndices (unsigned int *indices, int indexcount) { IndexBuffer.Write(indices,indexcount); }
	void WriteIndices (unsigned int *indices, int indexcount, int offset)  { IndexBuffer.Write(indices,indexcount, offset); }
	void WriteIndices (unsigned short *indices, int indexcount)  { IndexBuffer.Write(indices,indexcount); }
	void WriteIndices (unsigned short *indices, int indexcount, int offset) { IndexBuffer.Write(indices,indexcount, offset); }

	static Mesh LoadFromFile (const std::string &filename);
};

}}

