#include "Pipeline.h"
#include "RenderSystem.h"


namespace Tocs {
namespace Rendering {

Pipeline::Pipeline(RenderSystem &system)
: OpaquePipe(system),
  WireframePipe(system),
  TransparentPipe(system),
  DeferredPipe(system),
  ShadowPipe(system)
{

}

}}
