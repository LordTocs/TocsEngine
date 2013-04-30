#include "Init.h"

namespace Tocs {
namespace Rendering {

InitializationList &RenderInitList ()
{
	static InitializationList *list = new InitializationList ();
	return *list;
}

}}