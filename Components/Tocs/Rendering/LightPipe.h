#pragma once
#include "GBuffer.h"
#include "Pipe.h"
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/RenderTarget.h>
namespace Tocs {
namespace Rendering {

class LightPipe : public Pipe
{
	GBuffer &Buffer;
	Graphics::Texture2D FinalLightBuffer;
	Graphics::RenderTarget LightTarget;
protected:
	void BeginRender (const Camera &camera, Graphics::GraphicsContext &context);
	void EndRender (const Camera &camera, Graphics::GraphicsContext &context);
public:
	LightPipe(Graphics::GraphicsContext &context, GBuffer &buffer);


	
};

}}