#pragma once
#include "ShaderTypes.h"
namespace Tocs {
namespace Graphics{

class GPUType
{
	unsigned int Internal;

	GPUType(unsigned int format)
		: Internal(format) {}

public:
	const static GPUType Float;
	const static GPUType Vector2;
	const static GPUType Vector3;
	const static GPUType Vector4;
	const static GPUType Double;
	const static GPUType DVector2;
	const static GPUType DVector3;
	const static GPUType DVector4;
	const static GPUType Int;
	const static GPUType IVector2;
	const static GPUType IVector3;
	const static GPUType IVector4;
	const static GPUType UnsignedInt;
	const static GPUType UIVector2;
	const static GPUType UIVector3;
	const static GPUType UIVector4;
	const static GPUType Boolean;
	const static GPUType BVector2;
	const static GPUType BVector3;
	const static GPUType BVector4;
	const static GPUType Matrix;

	unsigned int GLEnum() const { return Internal; }
	unsigned int GLFormat() const;
	unsigned int SizeInBytes() const;
	unsigned int ComponentCount() const;

	ShaderVariableType ToShaderVariable() const;

};

}}