#pragma once

#include "RenderJob.h"
#include <Tocs/Math/Transform.h>
#include "MaterialPassSession.h"
#include "GeometryHandler.h"
//#include "Mesh.h"
namespace Tocs {
namespace Rendering {

class Mesh;
class MaterialPass;

class MeshJob : public RenderJob
{
	unsigned int Part;
	Mesh &ModelMesh;
	GeometryHandler &GeoHandler;
	MaterialPass &MeshPass;
public:
	MeshJob(Mesh &mesh, int part, MaterialPass &material, Math::Transform &trans, GeometryHandler &geometryhandler);
	
	void Render (const Camera &camera, Graphics::GraphicsContext &context);
};

}}
