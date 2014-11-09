#pragma once
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/Rendering/Material.h>
#include <Tocs/Rendering/Drawable.h>
#include <Tocs/Rendering/Geometry.h>
#include "Skeleton.h"
#include "AnimatedMesh.h"

namespace Tocs {
namespace Animation {


class AnimatedModel : public Rendering::Drawable
{
	static Asset<Graphics::ShaderCode> LoadAnimatedShader();
	static Asset<Graphics::ShaderCode> LoadAnimatedShaderWithVertex();
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadAnimatedShader> AnimatedShader;
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadAnimatedShaderWithVertex> AnimatedShaderWithVertex;

	class AnimatedGeometry : public Rendering::Geometry
	{
		AnimatedModel *Model;
		unsigned int Index;
		Rendering::Material GeometryMaterial;
		Graphics::ShaderState ShaderInputs;
	public:

		AnimatedGeometry(AnimatedModel *model, unsigned int index);
		AnimatedGeometry(const AnimatedGeometry &) = delete;
		AnimatedGeometry(AnimatedGeometry &&moveme);


		Rendering::DrawCall GetCall() const;
		void LinkShaders(Rendering::ShaderConstruction &construction, bool HasVertexComponent) const;
		void AddShaderInputs(Graphics::ShaderStateSet &input) const;

		void Queue();
		void DeQueue();

		Rendering::Material &GetMaterial() { return GeometryMaterial; }
		const Rendering::Material &GetMaterial() const { return GeometryMaterial; }
	};
	Skeleton Armature_;
	Asset<AnimatedMesh> SourceMesh;
	Graphics::Buffer<Math::Dual<Math::Quaternion>> PoseBuffer;
	std::vector<AnimatedGeometry> MeshParts;
public:
	Math::Transform Transform;
	AnimatedModel(Rendering::RenderSystem &system, const Asset<AnimatedMesh> &mesh);

	void QueueJobs();
	void DeQueueJobs();

	Rendering::Material &GetMaterial(unsigned int i);
	const Rendering::Material &GetMaterial(unsigned int i) const;

	unsigned int MaterialCount() const { return MeshParts.size(); }

	Skeleton &Armature() { return Armature_; }
	const Skeleton &Armature() const { return Armature_; }

	void Update(float dt);
};


}}


