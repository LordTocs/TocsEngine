#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/ShaderCode.h>
namespace Tocs {
namespace Rendering {

class TransparencyType
{
	enum InternalEnum
	{
		opaque,
		alpha,
		add
	};

	InternalEnum Internal;
	TransparencyType(InternalEnum i) : Internal(i) {}
public:
	const static TransparencyType Opaque;
	const static TransparencyType AlphaBlending;
	const static TransparencyType AdditiveBlending;

	TransparencyType() : Internal(opaque) {}

	const Asset<Graphics::ShaderCode> &GetCompositor() const;

	bool operator ==  (const TransparencyType &op2) const { return Internal == op2.Internal; }
	bool operator !=  (const TransparencyType &op2) const { return Internal != op2.Internal; }
};

}}



