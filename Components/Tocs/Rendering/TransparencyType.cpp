#include "TransparencyType.h"

namespace Tocs {
namespace Rendering {

const TransparencyType TransparencyType::Opaque(opaque);
const TransparencyType TransparencyType::AlphaBlending(alpha);
const TransparencyType TransparencyType::AdditiveBlending(add);

const Asset<Graphics::ShaderCode> &TransparencyType::GetCompositor() const
{
	static Asset<Graphics::ShaderCode> additivecompositor = Asset<Graphics::ShaderCode>::Load("shaders/transparency/AdditiveCompositor.frag");
	static Asset<Graphics::ShaderCode> alphacompositor = Asset<Graphics::ShaderCode>::Load("shaders/transparency/AlphaCompositor.frag");
	static Asset<Graphics::ShaderCode> opaquecompositor = Asset<Graphics::ShaderCode>::Load("shaders/transparency/OpaqueCompositor.frag");

	if (Internal == alpha)
	{
		return alphacompositor;
	}
	else if (Internal == add)
	{
		return additivecompositor;
	}

	return opaquecompositor;
}

}}
