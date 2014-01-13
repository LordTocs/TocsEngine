#pragma once
#include <vector>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Math/BoundingBox.h>
#include "MeshPart.h"
#include "DrawCall.h"

namespace Tocs {
namespace Rendering {

class Mesh
{
	Graphics::BufferBase VertexBuffer;
	Graphics::BufferBase IndexBuffer;
	Graphics::VAO VertexArray;
	Graphics::VertexFormat Format;
	std::vector <MeshPart> Parts;
	Math::BoundingBox BoundingBox;
public:
	Mesh(unsigned int vertexcount, unsigned int indexcount, const Graphics::VertexFormat &format);
	Mesh(unsigned int vertexcount, unsigned int indexcount, const Graphics::VertexFormat &format, const Graphics::IndexFormat &iformat);
	Mesh(Mesh &&moveme);

	Mesh(const Mesh &) = delete;

	const Graphics::BufferBase &GetVertexBuffer () const { return VertexBuffer; }
	const Graphics::BufferBase &GetIndexBuffer () const { return IndexBuffer; }

	unsigned int GetVerticeCount () const;
	unsigned int GetIndexCount () const;

	unsigned int PartCount () const { return Parts.size (); }

	DrawCall GetDrawCall (unsigned int index) const;

	const Math::BoundingBox &GetBounds () const { return BoundingBox; }

	void Bind () const;
	void UnBind () const;

	void AddPart (const MeshPart &part);

	Mesh &operator= (Mesh &&moveme);

	template <class T>
	void WriteVertices (T *data, int count) { VertexBuffer.Write(data,count * sizeof(T)); }

	void WriteIndices(unsigned int *data, unsigned int count) { IndexBuffer.Write(data, count * sizeof(unsigned int)); }
	void WriteIndices(unsigned short *data, unsigned int count) { IndexBuffer.Write(data, count * sizeof(unsigned short)); }

	static Mesh LoadFromFile (const std::string &filename);
};

}}

