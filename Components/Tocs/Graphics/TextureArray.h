#pragma once
#include "TextureFormat.h"

namespace Tocs {
namespace Graphics {

class TextureArray
{
	unsigned int ID;
	TextureFormat Format_;
	TextureFiltering Filtering_;
	unsigned int Width_;
	unsigned int Height_;
	unsigned int Layers_;
	void Build(unsigned int layers, unsigned int width, unsigned int height, TextureFormat format, TextureFiltering filtering);
public:
	TextureArray(unsigned int layers, unsigned int width, unsigned int height, TextureFormat format, TextureFiltering filtering);
	~TextureArray();

	TextureArray(TextureArray &&moveme);
	TextureArray &operator= (TextureArray &&moveme);

	TextureArray(const TextureArray &) = delete;
	TextureArray &operator= (const TextureArray &) = delete;

	unsigned int GetID() const { return ID; }

	unsigned int Width() const { return Width_; }
	unsigned int Height() const { return Height_; }
	unsigned int Layers() const { return Layers_; }

	const TextureFormat &Format() const { return Format_; }
	const TextureFiltering &Filtering() const { return Filtering_; }

	void Bind() const;
	void Bind(int Register) const;

	void UnBind() const;
	
	void SetData(TextureDataFormat format, const void *data, unsigned int layer);
	void Read(void *data, TextureDataFormat dataformat) const;

	static TextureArray LoadFromFile(const std::string &filename);
};

}}


