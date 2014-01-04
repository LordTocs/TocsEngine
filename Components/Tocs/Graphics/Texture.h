#pragma once

#include "TextureFormat.h"

namespace Tocs {
namespace Graphics {



class Texture2D
{
	unsigned int ID;
	Texture2D (const Texture2D &); //No Copying textures.

	TextureFormat Format_;
	TextureFiltering Filtering_;
	int Width_;
	int Height_;

	void BuildTexture (int width, int height, const TextureFiltering &filtering, const TextureFormat &format);

	Texture2D &operator= (const Texture2D &);
public:
	Texture2D(int width, int height, const TextureFiltering &filtering, const TextureFormat &format);
	Texture2D(Texture2D &&moveme);
	~Texture2D();

	unsigned int GetID () const { return ID; }

	const TextureFormat &Format () const {return Format_;}
	const TextureFiltering &Filtering () const {return Filtering_;}

	int Width () const { return Width_; };
	int Height () const { return Height_; };

	bool HasMipMaps () const;

	void Bind () const;
	void Bind (int Register) const;

	void BindImage(int Register, int Level) const;

	void UnBind () const;

	void SetData (TextureDataFormat format, void *data);

	Texture2D &operator= (Texture2D &&moveme);

	static Texture2D LoadFromFile (const std::string &filename);
};

}}