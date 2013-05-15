#include "RenderObject.h"

namespace Tocs {
namespace Rendering {

RenderObject::RenderObject(RenderSystem &system)
	: System(system),
	  Queued(false)
{
	System.AddObject(*this);
}

RenderObject::~RenderObject ()
{
	System.RemoveObject(*this);
}

void RenderObject::Update (float dt) 
{
	Transform.CreateMatrix();
}

}}