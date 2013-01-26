#include "MeshJob.h"
#include "Material.h"
#include "Mesh.h"
#include "ShaderPool.h"
namespace Tocs {
namespace Rendering {

MeshJob::MeshJob(Mesh &mesh, int part, MaterialPass &material, Math::Transform &trans, GeometryHandler &geometryhandler)
	: Part(part),
	  ModelMesh(mesh),
	  MeshPass(material),
	  RenderJob(trans,ShaderPool::Global.GetShader (geometryhandler,material.GetCompiledShader ())),
	  GeoHandler(geometryhandler)
{
}

void MeshJob::Render (const Camera &camera, Graphics::GraphicsContext &context)
{
	JobShader.Bind ();
	camera.PassToShader (JobShader);
	JobShader["World"] = Transformation.GetMatrix ();
	MeshPass.ApplyUniforms(JobShader);
	ModelMesh.PushPartGeometry (Part);
	JobShader.UnBind ();
}



}}