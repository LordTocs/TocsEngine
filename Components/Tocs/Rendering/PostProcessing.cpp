#include "PostProcessing.h"
#include "RenderSystem.h"
namespace Tocs {
namespace Rendering {

PostProcessing::PostProcessing(RenderSystem &system)
: System(&system)
, Target(false)
, FrameResultA(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8)
, FrameResultB(system.Context().GetTarget().GetWidth(), system.Context().GetTarget().GetHeight(), Graphics::TextureFiltering::None, Graphics::TextureFormat::RGBA8)
, AntiAliasing(*System)
{
	FrameTargetA.Bind();
	FrameTargetA.SetTexture(FrameResultB, 0);
	FrameTargetA.SetDepthBuffer(system.FrameDepth);
	FrameTargetA.UnBind();

	FrameTargetB.Bind();
	FrameTargetB.SetTexture(FrameResultA, 0);
	FrameTargetB.SetDepthBuffer(system.FrameDepth);
	FrameTargetB.UnBind();
}

void PostProcessing::Apply()
{
	System->Context().DisableDepthWrite();
	System->Context().DisableDepthTest();

	FlipTarget();
	AntiAliasing.Apply(GetCurrentFrameResult(), GetCurrentFrameTarget());
	FlipTarget();

	System->Context().EnableDepthWrite();
	System->Context().EnableDepthTest();
}

Graphics::Texture2D &PostProcessing::GetCurrentFrameResult()
{
	return (Target ? FrameResultA : FrameResultB);
}

Graphics::RenderTarget &PostProcessing::GetCurrentFrameTarget()
{
	return (Target ? FrameTargetA : FrameTargetB);
}

void PostProcessing::FlipTarget()
{
	Target = !Target;
}

}
}