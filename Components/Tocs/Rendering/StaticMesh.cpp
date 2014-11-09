#include "StaticMesh.h"

namespace Tocs {
namespace Rendering {

/////////////////////////////////////////////////////////////////
////////////////////    GEOMETRY    /////////////////////////////
/////////////////////////////////////////////////////////////////


StaticMesh::StaticGeometry::StaticGeometry(StaticMesh *mesh, unsigned int index)
: Mesh(mesh)
, Index(index) 
{
	ShaderInputs.AddValue("World").Ref(Mesh->Transform.GetMatrix());
}

StaticMesh::StaticGeometry::StaticGeometry(StaticGeometry &&moveme)
: Mesh(moveme.Mesh)
, Index(moveme.Index)
, GeometryMaterial(std::move(moveme.GeometryMaterial))
, ShaderInputs(std::move(moveme.ShaderInputs))
{

}

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

void StaticMesh::StaticGeometry::AddShaderInputs(Graphics::ShaderStateSet &input) const
{
	input.MapState(ShaderInputs);
}

void StaticMesh::StaticGeometry::Queue()
{
	GeometryMaterial.QueueJob(*this, Mesh->System);
}

void StaticMesh::StaticGeometry::DeQueue()
{
	GeometryMaterial.DeQueueJob();
}

void StaticMesh::StaticGeometry::UpdateBoundingBoxes()
{
	for (int i = 0; i < GeometryMaterial.ComponentCount(); ++i)
	{
		Math::BoundingBox box = Math::EncapsulateTransformedBoundingBox(Mesh->SourceMesh->GetBounds(Index), Mesh->Transform.GetMatrix());
		GeometryMaterial.GetComponent(i).GetJob().Bounds = box;
	}
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
	return Asset<Graphics::ShaderCode>::Load("shaders/StaticGeometryVertex.vert");
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

void StaticMesh::PreRenderUpdate(float dt)
{
	for (auto &part : MeshParts)
	{
		part.UpdateBoundingBoxes();
	}
}

}}