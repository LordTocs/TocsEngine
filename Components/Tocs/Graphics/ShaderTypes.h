#pragma once
#include <Tocs/Math/Vector3.h>
#include <Tocs/Math/Matrix4.h>
#include <string>

namespace Tocs {
namespace Graphics {

class ShaderVariableType
{
	enum InternalFormat
	{
		float_,
		vec2,
		vec3,
		vec4,
		mat4,
		int_,
		sampler2d,
		sampler2darray
	};
	InternalFormat Internal;

	ShaderVariableType (InternalFormat format)
		: Internal (format) {}

public:
	const static ShaderVariableType Float;
	const static ShaderVariableType Vector2;
	const static ShaderVariableType Vector3;
	const static ShaderVariableType Vector4;
	const static ShaderVariableType Matrix;
	const static ShaderVariableType Int;
	const static ShaderVariableType Sampler2D;
	const static ShaderVariableType Sampler2DArray;

	bool operator ==  (const ShaderVariableType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const ShaderVariableType &op2) const {return Internal != op2.Internal;}
	bool operator < (const ShaderVariableType &op2) const { return Internal < op2.Internal; }

	std::string ToString () const;
	std::string ToGLSLTypeString () const;

	static const ShaderVariableType & FromGLSLTypeString (const std::string &type);
	
	template <class T>
	static const ShaderVariableType &GetShaderVariableType ()
	{
		static_assert(false,"Unsupported Type: Cannot convert to Shader Variable Type");
	}

	template <>
	static const ShaderVariableType &GetShaderVariableType <int> ()
	{
		return Int;
	}

	template <>
	static const ShaderVariableType &GetShaderVariableType <float> ()
	{
		return Float;
	}

	template <>
	static const ShaderVariableType &GetShaderVariableType <Math::Vector3> ()
	{
		return Vector3;
	}

	template <>
	static const ShaderVariableType &GetShaderVariableType <Math::Matrix4> ()
	{
		return Matrix;
	}

	unsigned int VectorComponents () const;
	static std::string GetTruncationSwizzle (const ShaderVariableType &from, const ShaderVariableType &to);

	static ShaderVariableType FromGLUniformType (int type);

	unsigned int EnumIndex () const { return static_cast<unsigned int> (Internal); }
};

/*class ShaderPrototype
{
	std::string Name;
	ShaderVariableType Type;
public:
	ShaderPrototype (std::string name, ShaderVariableType type);
};*/

class ShaderType
{
	enum InternalFormat
	{
		vertex,
		pixel,
		geometry
	};
	InternalFormat Internal;

	ShaderType (InternalFormat format)
		: Internal (format) {}

public:
	const static ShaderType Vertex;
	const static ShaderType Pixel;
	const static ShaderType Geometry;

	bool operator == (const ShaderType &op2) const {return Internal == op2.Internal;}
	bool operator != (const ShaderType &op2) const {return Internal != op2.Internal;}
	bool operator <  (const ShaderType &op2) const {return Internal <  op2.Internal;}

	std::string ToString () const;
	
	unsigned int GetGLType () const;
	

	static ShaderType FromGLType (unsigned int gltype);
	
};


}}