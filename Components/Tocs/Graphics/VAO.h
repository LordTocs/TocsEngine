#pragma once
#include "Buffer.h"
#include "VertexFormat.h"

namespace Tocs {
namespace Graphics {

class VAO
{
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

	VAO &operator= (VAO &&moveme);
};

}}