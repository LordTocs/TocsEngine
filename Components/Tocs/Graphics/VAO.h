#pragma once
#include "Buffer.h"
#include "VertexFormat.h"
#include "IndexFormat.h"


namespace Tocs {
namespace Graphics {

class VAO
{
	IndexFormat Format;
	unsigned int ID;
	VAO (const VAO &);
public:
	VAO();
	~VAO();
	VAO(VAO &&moveme);

	unsigned int GetID () const { return ID; }

	void Bind () const;
	void UnBind () const;

	void AddVBO (const BufferBase &vbo, const VertexFormat &format);
	void AddIBO(const Buffer<unsigned int> &ibo);
	void AddIBO(const Buffer<unsigned short> &ibo);
	void AddIBO(const BufferBase &ibo, const IndexFormat &format);

	IndexFormat GetFormat() const { return Format; }

	VAO &operator= (VAO &&moveme);
};

}}