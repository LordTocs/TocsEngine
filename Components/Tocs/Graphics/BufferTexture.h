#pragma once
#include "Buffer.h"
#include "TextureFormat.h"
namespace Tocs {
namespace Graphics {

class BufferTexture
{
	unsigned int ID;
	TextureFormat Format;
public:
	BufferTexture(const BufferBase &buffer, TextureFormat format);
	BufferTexture(BufferTexture &&moveme);
	~BufferTexture();

	unsigned int GetID () const { return ID; }

	void Bind () const;
	void Bind (int Register) const;
	void BindImage(int Register) const;
	void UnBind () const;
};

}}