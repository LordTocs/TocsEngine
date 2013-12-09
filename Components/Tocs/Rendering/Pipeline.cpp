#include "Pipeline.h"
#include "RenderSystem.h"


namespace Tocs {
namespace Rendering {

Pipeline::Pipeline(Graphics::GraphicsContext &context, RenderSystem &system)
: ForwardPipe(system,context),
  WireframePipe(system,context)
{

}

}}
