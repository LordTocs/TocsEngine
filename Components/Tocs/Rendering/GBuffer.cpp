#include "GBuffer.h"
#include "RenderSystem.h"
#include <Tocs/Graphics/TextureFormat.h>

using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

GBuffer::GBuffer(Graphics::GraphicsContext &context, RenderSystem &system)
	: Albedo      (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::RGBA8),
	  Normals     (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::RGBA8),
	  Specular    (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::RGBA8),
	  LinearDepth (context.GetTarget().GetWidth(), context.GetTarget().GetHeight(), TextureFiltering::None, TextureFormat::R32)
{
	Target.SetTexture (Albedo,0);
	Target.SetTexture (Normals,1);
	Target.SetTexture (Specular,2);
	Target.SetTexture (LinearDepth,3);
	Target.SetDepthBuffer(system.FrameDepth);
}

void GBuffer::Bind ()
{
	Target.Bind ();
}

void GBuffer::UnBind ()
{
	Target.UnBind ();
}

}}