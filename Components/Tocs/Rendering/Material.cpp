#include "Material.h"
#include <Tocs/Core/Tokenizer.h>
#include "LightShader.h"
#include "WireframeShader.h"

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

void MaterialComponent::QueueJob(Geometry &geometry, Pipeline &pipeline)
{
	if (Proxy)
		Proxy.Remove();

	Proxy = MatSource->QueueJob(geometry, pipeline);
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
, Component(source.Get().GetComponent())
{
}

Material::Material(Material &&moveme)
: MatSource(std::move(moveme.MatSource))
, Component(std::move(moveme.Component))
{

}

Material::Material()
{}

void Material::QueueJob(Geometry &geometry, Pipeline &pipeline)
{
	if (MatSource)
	{
		Component.QueueJob(geometry, pipeline);
	}
}

void Material::DeQueueJob()
{
	if (MatSource)
	{
		Component.DeQueueJob();
	}
}

void Material::Source(const Asset<MaterialSource> &source)
{
	MatSource = source;
	Component.Source(source.Get().GetComponent());
}


///////////////////////////////////////////////////////////////
////////////////////    MATERIAL SOURCE    ////////////////////
///////////////////////////////////////////////////////////////


MaterialSource MaterialSource::LoadFromFile(const std::string &filename)
{
	Lexing::StringSource source = Lexing::StringSource::FromFile(filename);

	Lexing::Tokenizer tokens(source);

	MaterialSource mat;

	while (!tokens.EndOfStream())
	{
		Lexing::TokenData typetoken = tokens.GetTokenData();

		if (typetoken == "light")
		{
			mat.Component = std::unique_ptr<MaterialComponentSource>(new LightShader (LightShader::ParseFromConfig(tokens.GetTextIn("{", "}"))));
		}
		else if (typetoken == "wire")
		{
			mat.Component = std::unique_ptr<MaterialComponentSource>(new WireframeShader(WireframeShader::ParseFromConfig(tokens.GetTextIn("{", "}"))));
		}
		else if (typetoken == "deferred")
		{

		}
	}

	return std::move(mat);
}



}}
