#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Core/LateStatic.h>
#include <Tocs/Graphics/ShaderCode.h>
#include <Tocs/Math/Transform.h>
#include "Mesh.h"
#include "Drawable.h"
#include "Geometry.h"
#include "Material.h"
#include <vector>

namespace Tocs {
namespace Rendering {

class StaticMesh : public Drawable
{
	static Asset<Graphics::ShaderCode> LoadStaticShader();
	static Asset<Graphics::ShaderCode> LoadStaticShaderWithVertex();
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadStaticShader> StaticShader;
	static FirstUseStatic<Asset<Graphics::ShaderCode>, LoadStaticShaderWithVertex> StaticShaderWithVertex;

	class StaticGeometry : public Geometry
	{
		StaticMesh *Mesh;
		unsigned int Index;
		Material GeometryMaterial;
	public:

		StaticGeometry(StaticMesh *mesh, unsigned int index)
			: Mesh(mesh), Index(index) {}

		StaticGeometry(const StaticGeometry &) = delete;
		StaticGeometry(StaticGeometry &&moveme)
			: Mesh(moveme.Mesh), Index(moveme.Index), GeometryMaterial(std::move(moveme.GeometryMaterial)) {}


		DrawCall GetCall() const;
		void LinkShaders(ShaderConstruction &construction, bool HasVertexComponent) const;
		void AddShaderInputs(Graphics::ShaderInput &input) const;

		void Queue();
		void DeQueue();

		Material &GetMaterial() { return GeometryMaterial; }
		const Material &GetMaterial() const { return GeometryMaterial; }
	};

	Asset<Mesh> SourceMesh;

	std::vector<StaticGeometry> MeshParts;
	
public:
	friend class StaticGeometry;

	Math::Transform Transform;

	StaticMesh(RenderSystem &system, const Asset<Mesh> &mesh);

	StaticMesh(const StaticMesh &) = delete;

	void QueueJobs();
	void DeQueueJobs();

	Material &GetMaterial(unsigned int i);
	const Material &GetMaterial(unsigned int i) const;

	unsigned int MaterialCount() const { return MeshParts.size(); }

};

}}
