#include "StaticMesh.h"

namespace Tocs {
namespace Rendering {

/////////////////////////////////////////////////////////////////
////////////////////    GEOMETRY    /////////////////////////////
/////////////////////////////////////////////////////////////////

DrawCall StaticMesh::StaticGeometry::GetCall() const
{
	return Mesh->SourceMesh.Get().GetDrawCall(Index);
}
void StaticMesh::StaticGeometry::LinkShaders(ShaderConstruction &construction, bool HasVertexComponent) const
{
	if (HasVertexComponent)
	{
		construction.AddCode(StaticShaderWithVertex.Get().Get());
	}
	else
	{
		construction.AddCode(StaticShader.Get().Get());
	}
}

void StaticMesh::StaticGeometry::AddShaderInputs(Graphics::ShaderInput &input) const
{
	input["World"].Ref(Mesh->Transform.GetMatrix());
}

void StaticMesh::StaticGeometry::Queue()
{
	GeometryMaterial.QueueJob(*this, Mesh->System);
}

void StaticMesh::StaticGeometry::DeQueue()
{
	GeometryMaterial.DeQueueJob();
}

/////////////////////////////////////////////////////////////////
//////////////////////    MESH    ///////////////////////////////
/////////////////////////////////////////////////////////////////


Asset<Graphics::ShaderCode> StaticMesh::LoadStaticShader()
{
	return Asset<Graphics::ShaderCode>::Load("shaders/StaticGeometry.vert");
}

Asset<Graphics::ShaderCode> StaticMesh::LoadStaticShaderWithVertex()
{
	return Asset<Graphics::ShaderCode>::Load("shadersStaticGeometryVertex.vert");
}

FirstUseStatic<Asset<Graphics::ShaderCode>, StaticMesh::LoadStaticShader> StaticMesh::StaticShader;
FirstUseStatic<Asset<Graphics::ShaderCode>, StaticMesh::LoadStaticShaderWithVertex> StaticMesh::StaticShaderWithVertex;

StaticMesh::StaticMesh(RenderSystem &system, const Asset<Mesh> &mesh)
: Drawable(system),
  SourceMesh(mesh)
{
	MeshParts.reserve(SourceMesh.Get().PartCount());
	for (int i = 0; i < SourceMesh.Get().PartCount(); ++i)
	{
		MeshParts.emplace_back(this, i);
	}
}

void StaticMesh::QueueJobs()
{
	for (auto &part : MeshParts)
	{
		part.Queue();
	}
}

void StaticMesh::DeQueueJobs()
{
	for (auto &part : MeshParts)
	{
		part.DeQueue();
	}
}

Material &StaticMesh::GetMaterial(unsigned int i)
{
	return MeshParts[i].GetMaterial();
}

const Material &StaticMesh::GetMaterial(unsigned int i) const
{
	return MeshParts[i].GetMaterial();
}

}}