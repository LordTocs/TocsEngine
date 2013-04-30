#include "MaterialInstance.h"


namespace Tocs {
namespace Rendering {

MaterialInstance::MaterialComponent::MaterialComponent (RenderSystem &rsystem, const Material::MaterialComponent &basecomponent)
	: Template (basecomponent.GetTemplate()),
	  MaterialPipe (rsystem.Pipes.GetPipeByName(basecomponent.GetPipeName())),
	  MatShading (basecomponent.GetTemplate(),basecomponent.GetDefaultValues())
{

}

MaterialInstance::MaterialInstance(RenderSystem &rsystem, Asset<Material> material)
	: MaterialBase (material),
	  Components (material.Get().ComponentCount())
{
	for (auto i = material.Get().GetComponents().begin(); i != material.Get().GetComponents().end (); ++i)
	{
		Components.push_back (MaterialComponent (rsystem,(*i)));
	}
}




}}