#pragma once
#include "TextureFormat.h"
namespace Tocs {
namespace Graphics {

class CubeMapArray
{
	unsigned int ID;
public:
	CubeMapArray(unsigned int layers, unsigned int size, TextureFormat format, TextureFiltering filtering);
	~CubeMapArray();

	CubeMapArray(CubeMapArray &&moveme);
	CubeMapArray &operator= (CubeMapArray &&moveme);

	CubeMapArray(const CubeMapArray &) = delete;
	CubeMapArray &operator= (const CubeMapArray &) = delete;

	unsigned int GetID() const { return ID; }

	unsigned int GetSize() const;
	unsigned int GetLayers() const;

	void Bind() const;
	void Bind(int Register) const;

	void UnBind() const;

	void Build(unsigned int layers, unsigned int size, TextureFormat format, TextureFiltering filtering);

	void Read(void *data, TextureDataFormat dataformat) const;
};

}}
