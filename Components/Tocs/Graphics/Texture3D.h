#pragma once
#include "TextureFormat.h"
namespace Tocs {
namespace Graphics {

class Texture3D
{
	unsigned int ID;
	Texture3D (const Texture3D &); //No Copying textures.
	Texture3D &operator= (Texture3D &);
	TextureFormat _Format;
	TextureFiltering _Filtering;
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _Depth;

	void BuildTexture (unsigned int width, unsigned int height, unsigned int depth, const TextureFiltering &filtering, const TextureFormat &format);

	
public:
	Texture3D(unsigned int width, unsigned int height, unsigned int depth, const TextureFiltering &filtering, const TextureFormat &format);
	Texture3D(Texture3D &&moveme);
	~Texture3D();

	Texture3D &operator= (Texture3D &&moveme);

	unsigned int GetID () const { return ID; }

	const TextureFormat &Format () const {return _Format;}
	const TextureFiltering &Filtering () const {return _Filtering;}

	int Width () const { return _Width; };
	int Height () const { return _Height; };
	int Depth () const { return _Depth; }

	bool HasMipMaps () const;

	void Bind () const;
	void Bind (int Register) const;
	void UnBind () const;

	void SetData (TextureDataFormat format, void *data);
};

}}