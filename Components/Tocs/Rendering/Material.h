#pragma once
#include "Geometry.h"
#include "ShaderPool.h"
#include "Pipeline.h"
#include "Job.h"
#include <memory>
#include <vector>
#include <Tocs/Core/Asset.h>

namespace Tocs {
namespace Rendering {

class MaterialComponentSource
{
public:
	virtual ~MaterialComponentSource() {}
	MaterialComponentSource() {}
	MaterialComponentSource(MaterialComponentSource &&moveme) {}

	virtual Pipe &GetPipe(RenderSystem &system) const = 0;
	virtual void LinkShaderCode(ShaderConstruction &construction) const = 0;
	virtual void QueueJob(JobProxy &proxy, RenderSystem &system, Graphics::ShaderState &inputs) const = 0;
};

class MaterialComponent
{
	const MaterialComponentSource *MatSource;
	JobProxy Proxy;
public:
	Graphics::ShaderState Inputs;

	MaterialComponent();
	MaterialComponent(MaterialComponent &&moveme);
	MaterialComponent(const MaterialComponent &) = delete;
	MaterialComponent(const MaterialComponentSource &source);

	void Source(const MaterialComponentSource &source);

	void QueueJob(Geometry &geometry, RenderSystem &system);
	void DeQueueJob();

	const Job &GetJob() const { return Proxy.Get(); }
	Job &GetJob() { return Proxy.Get(); }
};

class MaterialSource
{
	std::vector<std::unique_ptr<MaterialComponentSource>> Components;
public:
	static MaterialSource LoadFromFile(const std::string &filename);
	static MaterialSource LoadFromConfig(const std::string &config);
	MaterialSource() {}
	MaterialSource(MaterialSource &&moveme) : Components(std::move(moveme.Components)) {}
	MaterialSource(const MaterialSource &) = delete;
	MaterialSource &operator=(const MaterialSource &) = delete;
	MaterialSource &operator=(MaterialSource &&moveme) { Components = std::move(moveme.Components); return *this; }

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

	void QueueJob(Geometry &geometry, RenderSystem &system);
	void DeQueueJob();

	unsigned int ComponentCount() const { return Components.size(); }
	MaterialComponent &GetComponent(unsigned int i) { return Components[i]; }
	const MaterialComponent &GetComponent(unsigned int i) const { return Components[i]; }
};

}}