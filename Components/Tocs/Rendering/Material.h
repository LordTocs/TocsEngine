#pragma once
#include "Geometry.h"
#include "ShaderPool.h"
#include "Pipeline.h"
#include "Job.h"
#include <memory>
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
	std::unique_ptr<MaterialComponentSource> Component;
public:
	static MaterialSource LoadFromFile(const std::string &filename);
	MaterialSource() {}
	MaterialSource(MaterialSource &&moveme) : Component(std::move(moveme.Component)) {}

	MaterialComponentSource &GetComponent() { return *Component.get(); }
	const MaterialComponentSource &GetComponent() const { return *Component.get(); }
};

class Material
{
	MaterialComponent Component;
	NullableAsset<MaterialSource> MatSource;
public:
	Material();
	Material(Material &&moveme);
	Material(const Material &) = delete;
	Material(Asset<MaterialSource> source);

	void Source(const Asset<MaterialSource> &source);

	void QueueJob(Geometry &geometry, Pipeline &pipeline);
	void DeQueueJob();

	MaterialComponent &GetComponent() { return Component; }
	const MaterialComponent &GetComponent() const { return Component; }
};

}}