#include "LightPipe.h"

using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

LightPipe::LightPipe(Graphics::GraphicsContext &context, GBuffer &buffer)
	: Buffer(buffer),
	  FinalLightBuffer(context.GetTarget().GetWidth (),context.GetTarget().GetHeight (),TextureFiltering::None, TextureFormat::RGBA8)
{
	LightTarget.SetTexture (FinalLightBuffer,0);
}


LightPipe::~LightPipe(void)
{
}

void LightPipe::BeginRender (const Camera &camera, Graphics::GraphicsContext &context)
{
	LightTarget.Bind ();
	context.ClearActiveBuffer ();
}
void LightPipe::EndRender (const Camera &camera, Graphics::GraphicsContext &context)
{
	LightTarget.UnBind ();
}

}}