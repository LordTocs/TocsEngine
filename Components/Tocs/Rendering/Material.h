#pragma once
#include <vector>
#include <memory>
#include "RenderSystem.h"
#include "MaterialValue.h"
#include "MaterialTemplate.h"
#include <Tocs/Core/Asset.h>

namespace Tocs {
namespace Rendering {

class MaterialInstance;

class Material
{
public:
	class MaterialComponent
	{
		Asset<MaterialTemplate> Template;
		MaterialValueSet Values;
		std::string PipeName;
	public:
		MaterialComponent (Asset<MaterialTemplate> matemplate, std::string pipename);
		const Asset<MaterialTemplate> &GetTemplate () const { return Template; }
		Asset<MaterialTemplate> &GetTemplate () { return Template; }

		const std::string &GetPipeName () const { return PipeName; }

		const MaterialValueSet &GetDefaultValues () const { return Values; }
	};
private:
	std::vector<MaterialComponent> Components;
public:
	Material();
	MaterialInstance *CreateInstance () const;

	int ComponentCount () const { return Components.size (); }

	const std::vector<MaterialComponent> &GetComponents () const { return Components; }

	
};

}}

