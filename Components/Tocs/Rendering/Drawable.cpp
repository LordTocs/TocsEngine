#include "Drawable.h"

namespace Tocs {
namespace Rendering {

Drawable::Drawable(RenderSystem &system)
	: System(system) 
{
	system.Add(*this);
}

Drawable::~Drawable()
{
	System.Remove(*this);
}

}}