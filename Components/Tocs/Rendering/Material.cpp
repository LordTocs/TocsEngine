#include "Material.h"
#include <Tocs/Core/Tokenizer.h>
#include "LightShader.h"
#include "WireframeShader.h"
#include "ShadowShader.h"
#include "UnlitShader.h"

namespace Tocs {
namespace Rendering {

///////////////////////////////////////////////////////////////
/////////////////////    MATERIAL COMPONENT    ////////////////
///////////////////////////////////////////////////////////////

MaterialComponent::MaterialComponent(const MaterialComponentSource &source)
: MatSource(&source)
{

}

MaterialComponent::MaterialComponent()
: MatSource(nullptr)
{
}

MaterialComponent::MaterialComponent(MaterialComponent &&moveme)
: MatSource(moveme.MatSource)
, Proxy(std::move(moveme.Proxy))
, Inputs(std::move(moveme.Inputs))
{
}

void MaterialComponent::Source(const MaterialComponentSource &source)
{
	MatSource = &source;
	if (Proxy)
	{
		Proxy.Remove();
	}
}

void MaterialComponent::QueueJob(Geometry &geometry, RenderSystem &system)
{
	if (Proxy)
		Proxy.Remove();

	Proxy = MatSource->QueueJob(geometry, system);
	geometry.AddShaderInputs(Proxy.Get().Input);
	Proxy.Get().Input.ApplyMap(Inputs);
}

void MaterialComponent::DeQueueJob()
{
	if (Proxy)
		Proxy.Remove();
}

///////////////////////////////////////////////////////////////
////////////////////////    MATERIAL   ////////////////////////
///////////////////////////////////////////////////////////////


Material::Material(Asset<MaterialSource> source)
: MatSource(source)
{
	for (int i = 0; i < source.Get().ComponentCount(); ++i)
	{
		Components.emplace_back(source.Get().GetComponent(i));
	}
}

Material::Material(Material &&moveme)
: MatSource(std::move(moveme.MatSource))
{

}

Material::Material()
{}

void Material::QueueJob(Geometry &geometry, RenderSystem &system)
{
	if (MatSource)
	{
		for (auto &c : Components)
		{
			c.QueueJob(geometry, system);
		}
	}
}

void Material::DeQueueJob()
{
	if (MatSource)
	{
		for (auto &c : Components)
		{
			c.DeQueueJob();
		}
	}
}

void Material::Source(const Asset<MaterialSource> &source)
{
	MatSource = source;
	Components.clear();
	for (int i = 0; i < source.Get().ComponentCount(); ++i)
	{
		Components.emplace_back(source.Get().GetComponent(i));
	}
}


///////////////////////////////////////////////////////////////
////////////////////    MATERIAL SOURCE    ////////////////////
///////////////////////////////////////////////////////////////


MaterialSource MaterialSource::LoadFromFile(const std::string &filename)
{
	Lexing::StringSource source = Lexing::StringSource::FromFile(filename);

	return LoadFromConfig(source.GetString());
	
}

MaterialSource MaterialSource::LoadFromConfig(const std::string &config)
{
	Lexing::StringSource source(config);
	Lexing::Tokenizer tokens(source);

	MaterialSource mat;

	while (!tokens.EndOfStream())
	{
		Lexing::TokenData typetoken = tokens.GetTokenData();

		if (typetoken == "light")
		{
			mat.Components.emplace_back(new LightShader(LightShader::ParseFromConfig(tokens.GetTextIn("{", "}"))));
		}
		else if (typetoken == "wire")
		{
			mat.Components.emplace_back(new WireframeShader(WireframeShader::ParseFromConfig(tokens.GetTextIn("{", "}"))));
		}
		else if (typetoken == "shadow")
		{
			mat.Components.emplace_back(new ShadowShader(ShadowShader::ParseFromConfig(tokens.GetTextIn("{", "}"))));
		}
		else if (typetoken == "unlit")
		{
			mat.Components.emplace_back(new UnlitShader(UnlitShader::ParseFromConfig(tokens.GetTextIn("{", "}"))));
		}
	}

	return std::move(mat);
}



}}
