#include "Job.h"

namespace Tocs {
namespace Rendering {

void Job::Render (Graphics::GraphicsContext &context, const Camera &cam)
{
	BuiltShader.Bind ();
	cam.PassToShader(BuiltShader);
	Geom->PassToShader(BuiltShader);
	Geom->Prep(cam);
	Shad->PassToShader(BuiltShader,cam);
	Pipe->ApplyPipeInputs(context,cam,BuiltShader);
	Geom->PushGeometry(GeometryIndex);
	BuiltShader.UnBind ();
}

}}


