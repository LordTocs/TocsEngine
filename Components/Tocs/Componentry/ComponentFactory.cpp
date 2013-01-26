#include "ComponentFactory.h"

namespace Tocs {
namespace Componentry {

ComponentRegistry &ComponentRegistry::GetRegistry ()
{
	static ComponentRegistry *Registry = new ComponentRegistry ();
	return *Registry;
}

}}