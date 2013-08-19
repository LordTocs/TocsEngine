#pragma once
#include "Texture.h"
#include "DepthStencilBuffer.h"
#include <vector>
namespace Tocs {
namespace Graphics {

class RenderTarget
{
	int ID;
	std::vector <int> BufferList;
	void InternalBind ();
public:
	RenderTarget(void);
	~RenderTarget(void);

	void SetTexture (const Texture2D &texture, int output);
	void SetDepthBuffer (const DepthStencilBuffer &depth);

	void Bind ();
	static void UnBind ();

	void DebugCompleteness ();
};

}}