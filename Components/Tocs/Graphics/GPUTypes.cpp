#include "GPUTypes.h"
#include "GLHeader.h"
namespace Tocs {
namespace Graphics
{

const GPUType GPUType::Float(GL_FLOAT);
const GPUType GPUType::Vector2(GL_FLOAT_VEC2);
const GPUType GPUType::Vector3(GL_FLOAT_VEC3);
const GPUType GPUType::Vector4(GL_FLOAT_VEC4);
const GPUType GPUType::Double(GL_DOUBLE);
const GPUType GPUType::DVector2(GL_DOUBLE_VEC2);
const GPUType GPUType::DVector3(GL_DOUBLE_VEC3);
const GPUType GPUType::DVector4(GL_DOUBLE_VEC4);
const GPUType GPUType::Int(GL_INT);
const GPUType GPUType::IVector2(GL_INT_VEC2);
const GPUType GPUType::IVector3(GL_INT_VEC3);
const GPUType GPUType::IVector4(GL_INT_VEC4);
const GPUType GPUType::UnsignedInt(GL_UNSIGNED_INT);
const GPUType GPUType::UIVector2(GL_UNSIGNED_INT_VEC2);
const GPUType GPUType::UIVector3(GL_UNSIGNED_INT_VEC3);
const GPUType GPUType::UIVector4(GL_UNSIGNED_INT_VEC4);
const GPUType GPUType::Boolean(GL_BOOL);
const GPUType GPUType::BVector2(GL_BOOL_VEC2);
const GPUType GPUType::BVector3(GL_BOOL_VEC3);
const GPUType GPUType::BVector4(GL_BOOL_VEC4);
const GPUType GPUType::Matrix(GL_FLOAT_MAT4);

unsigned int GPUType::GLFormat() const
{
	switch (Internal)
	{
	case GL_FLOAT:
	case GL_FLOAT_VEC2:
	case GL_FLOAT_VEC3:
	case GL_FLOAT_VEC4:
	case GL_FLOAT_MAT4:
		return GL_FLOAT;
	case GL_DOUBLE:
	case GL_DOUBLE_VEC2:
	case GL_DOUBLE_VEC3:
	case GL_DOUBLE_VEC4:
		return GL_DOUBLE;
	case GL_INT:
	case GL_INT_VEC2:
	case GL_INT_VEC3:
	case GL_INT_VEC4:
		return GL_INT;
	case GL_UNSIGNED_INT:
	case GL_UNSIGNED_INT_VEC2:
	case GL_UNSIGNED_INT_VEC3:
	case GL_UNSIGNED_INT_VEC4:
		return GL_UNSIGNED_INT;
	case GL_BOOL:
	case GL_BOOL_VEC2:
	case GL_BOOL_VEC3:
	case GL_BOOL_VEC4:
		return GL_BOOL;
	}
	return GL_INVALID_ENUM;
}
unsigned int GPUType::SizeInBytes() const
{
	switch (Internal)
	{
	case GL_FLOAT:
		return 4;
	case GL_FLOAT_VEC2:
		return 8;
	case GL_FLOAT_VEC3:
		return 12;
	case GL_FLOAT_VEC4:
		return 16;
	case GL_FLOAT_MAT4:
		return 4 * 16;
	case GL_DOUBLE:
		return 8;
	case GL_DOUBLE_VEC2:
		return 16;
	case GL_DOUBLE_VEC3:
		return 24;
	case GL_DOUBLE_VEC4:
		return 32;
	case GL_INT:
		return 4;
	case GL_INT_VEC2:
		return 8;
	case GL_INT_VEC3:
		return 12;
	case GL_INT_VEC4:
		return 16;
	case GL_UNSIGNED_INT:
		return 4;
	case GL_UNSIGNED_INT_VEC2:
		return 8;
	case GL_UNSIGNED_INT_VEC3:
		return 12;
	case GL_UNSIGNED_INT_VEC4:
		return 16;
	case GL_BOOL:
		return 4;
	case GL_BOOL_VEC2:
		return 8;
	case GL_BOOL_VEC3:
		return 12;
	case GL_BOOL_VEC4:
		return 16;
	}
	return 0;
}

unsigned int GPUType::ComponentCount() const
{
	switch (Internal)
	{
	case GL_FLOAT:
	case GL_DOUBLE:
	case GL_INT:
	case GL_UNSIGNED_INT:
	case GL_BOOL:
		return 1;
	case GL_FLOAT_VEC2:
	case GL_DOUBLE_VEC2:
	case GL_INT_VEC2:
	case GL_UNSIGNED_INT_VEC2:
	case GL_BOOL_VEC2:
		return 2;
	case GL_FLOAT_VEC3:
	case GL_DOUBLE_VEC3:
	case GL_INT_VEC3:
	case GL_UNSIGNED_INT_VEC3:
	case GL_BOOL_VEC3:
		return 3;
	case GL_FLOAT_VEC4:
	case GL_DOUBLE_VEC4:
	case GL_INT_VEC4:
	case GL_UNSIGNED_INT_VEC4:
	case GL_BOOL_VEC4:
		return 4;
	}
	return 0;
}

ShaderVariableType GPUType::ToShaderVariable() const
{
	return ShaderVariableType::FromGLUniformType(Internal);
}

}}