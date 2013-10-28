#pragma once
#include "TBO.h"
#include "TextureFormat.h"
namespace Tocs {
namespace Graphics {

class BufferTexture
{
	unsigned int ID;
public:
	BufferTexture(const TBO &buffer, TextureFormat format);
	BufferTexture(BufferTexture &&moveme);
	~BufferTexture();

	unsigned int GetID () const { return ID; }

	void Bind () const;
	void Bind (int Register) const;
	void UnBind () const;
};

}}