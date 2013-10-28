#include "Compositor.h"

namespace Tocs {
namespace Rendering {

FrameBufferCompositor::FrameBufferCompositor ()
	: CompositingShader (Asset<Graphics::ShaderCode>::Load("FrameBufferCompositer.frag"))
{
}

}}
