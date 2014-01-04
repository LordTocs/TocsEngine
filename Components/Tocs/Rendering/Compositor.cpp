#include "Compositor.h"

namespace Tocs {
namespace Rendering {

FrameBufferCompositor::FrameBufferCompositor ()
: CompositingShader (Asset<Graphics::ShaderCode>::Load("FrameBufferCompositor.frag"))
{
}

TransparencyCompositor::TransparencyCompositor()
: CompositingShader(Asset<Graphics::ShaderCode>::Load("transparency/Compositor.frag"))
{

}

}}
