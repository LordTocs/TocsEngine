#include "PointLightJob.h"
#include "PointLight.h"
namespace Tocs {
namespace Rendering {

PointLightJob::PointLightJob(PointLight *light)
	: Light(light), RenderJob (light->Transform,light->PointLightShader.Get ())
{
}

void PointLightJob::Render (const Camera &camera, Graphics::GraphicsContext &context)
{
	JobShader.Bind ();
	camera.PassToShader (JobShader);

	JobShader.UnBind ();
}

}}