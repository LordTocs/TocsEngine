#pragma once
#include <Tocs/Rendering/Mesh.h>
#include <Tocs/Rendering/Material.h>
#include <Tocs/Rendering/Drawable.h>
#include <Tocs/Rendering/Geometry.h>

namespace Tocs {
namespace Animation {


class AnimatedMesh : public Rendering::Drawable
{
	static Asset<Graphics::ShaderCode> LoadAnimatedShader();
	static Asset<Graphics::ShaderCode> LoadAnimatedShaderWithVertex();
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadAnimatedShader> AnimatedShader;
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadAnimatedShaderWithVertex> AnimatedShaderWithVertex;

	class AnimatedGeometry : public Rendering::Geometry
	{
		AnimatedMesh *Mesh;
		unsigned int Index;
		Rendering::Material GeometryMaterial;
	public:

		AnimatedGeometry(AnimatedMesh *mesh, unsigned int index)
			: Mesh(mesh), Index(index) {}

		AnimatedGeometry(const AnimatedGeometry &) = delete;
		AnimatedGeometry(AnimatedGeometry &&moveme)
			: Mesh(moveme.Mesh), Index(moveme.Index), GeometryMaterial(std::move(moveme.GeometryMaterial)) {}


		Rendering::DrawCall GetCall() const;
		void LinkShaders(AnimatedGeometry &construction, bool HasVertexComponent) const;
		void AddShaderInputs(Graphics::ShaderInput &input) const;

		void Queue();
		void DeQueue();

		Rendering::Material &GetMaterial() { return GeometryMaterial; }
		const Rendering::Material &GetMaterial() const { return GeometryMaterial; }
	};

	Asset<Rendering::Mesh> SourceMesh;

	std::vector<AnimatedGeometry> MeshParts;
public:


	void QueueJobs();
	void DeQueueJobs();

	Rendering::Material &GetMaterial(unsigned int i);
	const Rendering::Material &GetMaterial(unsigned int i) const;

	unsigned int MaterialCount() const { return MeshParts.size(); }
};


}}


