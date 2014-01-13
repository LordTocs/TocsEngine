#pragma once
#include "Geometry.h"
#include "ShaderPool.h"
#include "Pipeline.h"
#include "Job.h"
#include <memory>
#include <vector>
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/UniformMap.h>

namespace Tocs {
namespace Rendering {

class MaterialComponentSource
{
public:
	virtual ~MaterialComponentSource() {}
	MaterialComponentSource() {}
	MaterialComponentSource(MaterialComponentSource &&moveme) {}


	virtual void LinkShaderCode(ShaderConstruction &construction) const = 0;
	virtual JobProxy QueueJob(Geometry &geometry, Pipeline &pipeline) const = 0;
};

class MaterialComponent
{
	const MaterialComponentSource *MatSource;
	JobProxy Proxy;
public:
	Graphics::UniformMap Inputs;

	MaterialComponent();
	MaterialComponent(MaterialComponent &&moveme);
	MaterialComponent(const MaterialComponent &) = delete;
	MaterialComponent(const MaterialComponentSource &source);

	void Source(const MaterialComponentSource &source);

	void QueueJob(Geometry &geometry, Pipeline &pipeline);
	void DeQueueJob();
};

class MaterialSource
{
	std::vector<std::unique_ptr<MaterialComponentSource>> Components;
public:
	static MaterialSource LoadFromFile(const std::string &filename);
	MaterialSource() {}
	MaterialSource(MaterialSource &&moveme) : Components(std::move(moveme.Components)) {}


	unsigned int ComponentCount() const { return Components.size(); }
	MaterialComponentSource &GetComponent(unsigned int i) { return *Components[i].get(); }
	const MaterialComponentSource &GetComponent(unsigned int i) const { return *Components[i].get(); }
};

class Material
{
	std::vector<MaterialComponent> Components;
	NullableAsset<MaterialSource> MatSource;
public:
	Material();
	Material(Material &&moveme);
	Material(const Material &) = delete;
	Material(Asset<MaterialSource> source);

	void Source(const Asset<MaterialSource> &source);

	void QueueJob(Geometry &geometry, Pipeline &pipeline);
	void DeQueueJob();

	MaterialComponent &GetComponent(unsigned int i) { return Components[i]; }
	const MaterialComponent &GetComponent(unsigned int i) const { return Components[i]; }
};

}}