#include "AnimatedModel.h"

namespace Tocs {
namespace Animation {

/////////////////////////////////////////////////////////////////
////////////////////    GEOMETRY    /////////////////////////////
/////////////////////////////////////////////////////////////////

Rendering::DrawCall AnimatedModel::AnimatedGeometry::GetCall() const
{
	return Model->SourceMesh.Get().Mesh().GetDrawCall(Index);
}
void AnimatedModel::AnimatedGeometry::LinkShaders(Rendering::ShaderConstruction &construction, bool HasVertexComponent) const
{
	if (HasVertexComponent)
	{
		construction.AddCode(AnimatedShaderWithVertex.Get().Get());
	}
	else
	{
		construction.AddCode(AnimatedShader.Get().Get());
	}
}

void AnimatedModel::AnimatedGeometry::AddShaderInputs(Graphics::ShaderInput &input) const
{
	input["World"].Ref(Model->Transform.GetMatrix());
	input["BoneBuffer"].Ref(Model->PoseBuffer);
}

void AnimatedModel::AnimatedGeometry::Queue()
{
	GeometryMaterial.QueueJob(*this, Model->System);
}

void AnimatedModel::AnimatedGeometry::DeQueue()
{
	GeometryMaterial.DeQueueJob();
}


/////////////////////////////////////////////////////////////////
//////////////////////    MESH    ///////////////////////////////
/////////////////////////////////////////////////////////////////


Asset<Graphics::ShaderCode> AnimatedModel::LoadAnimatedShader()
{
	return Asset<Graphics::ShaderCode>::Load("shaders/animation/AnimatedGeometry.vert");
}

Asset<Graphics::ShaderCode> AnimatedModel::LoadAnimatedShaderWithVertex()
{
	return Asset<Graphics::ShaderCode>::Load("shaders/animation/AnimatedGeometry.vert");
}

FirstUseStatic<Asset<Graphics::ShaderCode>, AnimatedModel::LoadAnimatedShader> AnimatedModel::AnimatedShader;
FirstUseStatic<Asset<Graphics::ShaderCode>, AnimatedModel::LoadAnimatedShaderWithVertex> AnimatedModel::AnimatedShaderWithVertex;

AnimatedModel::AnimatedModel(Rendering::RenderSystem &system, const Asset<AnimatedMesh> &mesh)
: Drawable(system)
, SourceMesh(mesh)
, Armature_(mesh.Get().Armature())
, PoseBuffer(mesh.Get().Armature().BoneCount())
{
	MeshParts.reserve(SourceMesh.Get().Mesh().PartCount());
	for (int i = 0; i < SourceMesh.Get().Mesh().PartCount(); ++i)
	{
		MeshParts.emplace_back(this, i);
	}
}

void AnimatedModel::QueueJobs()
{
	for (auto &part : MeshParts)
	{
		part.Queue();
	}
}

void AnimatedModel::DeQueueJobs()
{
	for (auto &part : MeshParts)
	{
		part.DeQueue();
	}
}

Rendering::Material &AnimatedModel::GetMaterial(unsigned int i)
{
	return MeshParts[i].GetMaterial();
}

const Rendering::Material &AnimatedModel::GetMaterial(unsigned int i) const
{
	return MeshParts[i].GetMaterial();
}

void AnimatedModel::Update(float dt)
{
	Armature_.ComputePoses();
	PoseBuffer.Write(Armature_.GetPoses());
}

}
}


