#pragma once
#include <vector>
#include <Tocs/Core/Asset.h>
#include "MaterialTemplate.h"
#include "MaterialValue.h"
#include "RenderSystem.h"
#include "Pipe.h"
#include "MaterialShading.h"

#include "Material.h"

namespace Tocs {
namespace Rendering {

class MaterialInstance
{
public:
	class MaterialComponent
	{	
		Asset<MaterialTemplate> Template;
		Pipe *MaterialPipe;
		MaterialShading MatShading;
	public:
		Pipe &GetPipe () { return *MaterialPipe; }
		const Pipe &GetPipe () const { return *MaterialPipe; }

		MaterialComponent (RenderSystem &rsystem, const Material::MaterialComponent &basecomponent);

		MaterialValueSet::MaterialValueHolder &operator[] (const std::string &value)
		{ return MatShading[value]; }

		const MaterialValueSet::MaterialValueHolder &operator[] (const std::string &value) const
		{ return MatShading[value]; }

		const MaterialShading &GetShading () const { return MatShading; }
	};
private:
	Asset<Material> MaterialBase;
	std::vector<MaterialComponent> Components;
public:
	MaterialInstance(RenderSystem &rsystem, Asset<Material> material);

	std::vector<MaterialComponent> &GetComponents() { return Components; }
	const std::vector<MaterialComponent> &GetComponents() const { return Components; }

};


}}