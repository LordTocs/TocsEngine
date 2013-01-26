#include "Pipe.h"

namespace Tocs {
namespace Rendering {

Pipe::Pipe(void)
{
}


Pipe::~Pipe(void)
{
}

void Pipe::Render (const Camera &camera, Graphics::GraphicsContext &context)
{
	BeginRender (camera,context);
	for (auto i = Jobs.begin (); i != Jobs.end (); ++i)
	{
		if ((*i)->IsVisible (camera))
		{
			(*i)->Render(camera,context);
		}
	}
	EndRender (camera,context);
}

}}