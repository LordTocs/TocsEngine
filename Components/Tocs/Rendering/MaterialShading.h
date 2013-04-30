#pragma once
#include <Tocs/Core/Asset.h>
#include "Shading.h"
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/UniformMap.h>
#include "MaterialTemplate.h"
#include "MaterialValue.h"

namespace Tocs {
namespace Rendering {

class MaterialShading;

class MaterialShadingType : public ShadingType
{
	Asset<MaterialTemplate> Template;
	MaterialShading *MatShading;
public:
	MaterialShadingType (MaterialShading *shading, Asset<MaterialTemplate> matemplate)
		: MatShading(shading),
	      Template(matemplate)
	{}

	void AddShaders (Graphics::Shader &targetshader) const;
};

class MaterialShading : public Shading
{
	MaterialShadingType MatType;
public:
	MaterialValueSet Values;
	explicit MaterialShading(Asset<MaterialTemplate> matemplate)
		: Values(matemplate), MatType (this,matemplate) {}

	MaterialShading(Asset<MaterialTemplate> matemplate, const MaterialValueSet &matvalues)
		: Values(matvalues), MatType (this,matemplate) {}

	const ShadingType &GetType () const { return MatType; }

	MaterialValueSet::MaterialValueHolder &operator[] (const std::string &value)
	{ return Values[value]; }

	const MaterialValueSet::MaterialValueHolder &operator[] (const std::string &value) const
	{ return Values[value]; }

	void PassToShader (Graphics::Shader &shader) const
	{
		Values.PassToShader (shader);
	}
};

}}
