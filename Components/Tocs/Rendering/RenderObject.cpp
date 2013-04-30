#include "RenderObject.h"

namespace Tocs {
namespace Rendering {

RenderObject::RenderObject(RenderSystem &system)
	: System(system)
{

}

RenderObject::~RenderObject ()
{

}

void RenderObject::Update (float dt) {}

}}