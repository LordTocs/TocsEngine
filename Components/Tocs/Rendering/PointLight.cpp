#include "PointLight.h"
#include "Primitives.h"
#include <cmath>
namespace Tocs {
namespace Rendering {

void LightCubeGeometry::Prep (const Camera &cam) const
{
	Math::Vector3 diff = cam.Position - Light->Transform.GetWorldPosition ();
	const_cast<bool &>(Invert) = (std::abs(diff.X) < Light->Radius ||
		                          std::abs(diff.Y) < Light->Radius ||
		                          std::abs(diff.Z) < Light->Radius);
}

void LightCubeGeometry::PushGeometry (unsigned int part) const
{ 
	if (!Invert)
	{
		MeshBuffer->Bind ();
		MeshBuffer->PushPartGeometry (part);
		MeshBuffer->UnBind ();
	}
	else
	{
		InverseMeshBuffer->Bind ();
		InverseMeshBuffer->PushPartGeometry (part);
		InverseMeshBuffer->UnBind ();
	}
}

void PointLight::QueueJobs ()
{
	System.Pipes.DeferredLightPipe.AppendJob(DeferredJob);
}

void PointLight::DequeueJobs ()
{
	System.Pipes.DeferredLightPipe.RemoveJob(DeferredJob);
}

PointLight::PointLight(RenderSystem &system)
	: RenderObject(system),
	  LightGeometry (this),
	  LightShadingType (Asset<BasicShadingType>::Load("PointLight.frag")),
	  LightShading (LightShadingType.Get()),
	  DeferredJob (LightGeometry,LightShading),
	  Intensity(1),
	  Radius(10),
	  Color (255,255,255)
{
	LightShading["LightPosition"].Value (Transform.GetWorldPosition()); //What do?
	LightShading["LightColor"].Ref(Color);
	LightShading["LightIntensityCoefficient"].Ref (Intensity);
	LightShading["LightRadius"].Ref(Radius);
}

void PointLight::Update(float dt)
{
	RenderObject::Update(dt);
	LightGeometry["World"].Value (Math::Matrix4::CreateTranslation (Transform.GetWorldPosition()) * Math::Matrix4::CreateScale (Radius,Radius,Radius));
	LightShading["LightPosition"].Value (Transform.GetWorldPosition());
	
}

}}