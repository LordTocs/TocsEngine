#include "RenderSystem.h"
#include "RenderObject.h"
#include <algorithm>

namespace Tocs {
namespace Rendering {

RenderSystem::RenderSystem(Graphics::GraphicsContext  &context)
	: Pipes(context)
{
}

void RenderSystem::Render (Graphics::GraphicsContext &context,const Camera &cam)
{
	Pipes.DeferredPipe.Render (context,cam);
	Pipes.DeferredLightPipe.Render (context,cam);
	Pipes.UnlitPipe.Render (context,cam);
	Pipes.WireframePipe.Render (context,cam);
}

void RenderSystem::Update (float dt)
{	
	for (auto i = Objects.begin (); i != Objects.end (); ++i)
	{
		(*i)->Update(dt);
	}
}

void RenderSystem::AddObject (RenderObject &object)
{
	Objects.push_back(&object);
}
void RenderSystem::RemoveObject (RenderObject &object)
{
	auto i = std::find(Objects.begin(),Objects.end(),&object);
	if (i != Objects.end ())
	{
		Objects.erase(i);
	}
}

}}