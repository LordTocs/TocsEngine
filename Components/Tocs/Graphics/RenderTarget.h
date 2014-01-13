#pragma once
#include "Texture.h"
#include "DepthStencilBuffer.h"
#include "CubeMapArray.h"
#include <vector>
namespace Tocs {
namespace Graphics {

class RenderTarget
{
	int ID;
	std::vector <int> BufferList;
	void InternalBind ();

	void AddBufferFlag(int flag);
public:
	RenderTarget(void);
	~RenderTarget(void);

	void SetTexture (const Texture2D &texture, int output);
	void SetDepthBuffer (const DepthStencilBuffer &depth);
	void SetCubeMapArraySide(const CubeMapArray &arr, int layer, int face, int output);
	void SetDepthCubeMapArraySide(const CubeMapArray &arr, int layer, int face);

	void Bind ();
	static void UnBind ();

	void DebugCompleteness ();
};

}}