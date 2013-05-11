#pragma once
#include <Tocs/Core/Asset.h>
#include "Shading.h"
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/UniformMap.h>
#include "MaterialTemplate.h"
#include "MaterialValue.h"
#include <iostream>

namespace Tocs {
namespace Rendering {

class MaterialShading;

class MaterialShadingType : public ShadingType
{
	
	
public:
	Asset<MaterialTemplate> Template;
	MaterialShading *MatShading;
	MaterialShadingType (MaterialShading *shading, Asset<MaterialTemplate> matemplate)
		: MatShading(shading),
	      Template(matemplate)
	{}

	void AddShaders (Graphics::Shader &targetshader) const;
};

class MaterialShading : public Shading
{
public:
	MaterialValueSet Values;
private:
	MaterialShadingType MatType;
public:
	
	explicit MaterialShading(Asset<MaterialTemplate> matemplate)
		: Values(matemplate), MatType (this,matemplate) 
	{
		
	}

	MaterialShading (const MaterialShading &copyme)
		: Values(copyme.Values), MatType(this,copyme.MatType.Template)
	{
	}
	MaterialShading &operator= (const MaterialShading &copyme)
	{
		Values = copyme.Values;
		MatType = MaterialShadingType(this,copyme.MatType.Template);
	}

	MaterialShading(Asset<MaterialTemplate> matemplate, const MaterialValueSet &matvalues)
		: Values(matvalues), MatType (this,matemplate) 
	{
		std::cout << this << " " << MatType.MatShading << std::endl;
	}

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
