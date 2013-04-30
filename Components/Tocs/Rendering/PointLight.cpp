#include "PointLight.h"

namespace Tocs {
namespace Rendering {

void PointLight::QueueJobs ()
{
	System.Pipes.DeferredLightPipe.AppendJob(DeferredJob);
}

void PointLight::DequeueJobs ()
{
	System.Pipes.DeferredLightPipe.AppendJob(DeferredJob);
}

PointLight::PointLight(RenderSystem &system)
	: RenderObject(system),
	  LightGeometry (LightHulls::Cube.Get (),LightHulls::GeometryType.Get()),
	  LightShadingType (Asset<BasicShadingType>::Load("PointLight.frag")),
	  LightShading (LightShadingType.Get()),
	  DeferredJob (LightGeometry,LightShading),
	  Intensity(1),
	  Radius(10)
{
	LightShading["LightPosition"].Value (Transform.GetWorldPosition()); //What do?
	LightShading["LightColor"].Ref(Color);
	LightShading["LightIntensityCoefficient"].Ref (Intensity);
	LightShading["LightRadius"].Ref(Radius);
}

void PointLight::Update(float dt)
{
	LightGeometry["World"].Value (Math::Matrix4::CreateScale (Radius,Radius,Radius) * Math::Matrix4::CreateTranslation (Transform.GetWorldPosition()));
	LightShading["LightPosition"].Value (Transform.GetWorldPosition());
	
}

}}