#pragma once
#include <Tocs/Math/Vector.h>
#include <Tocs/Math/Matrix4.h>
#include <string>

namespace Tocs {
namespace Graphics {

class ShaderVariableType
{
	unsigned int Internal;

	ShaderVariableType (unsigned int format)
		: Internal (format) {}

public:
	const static ShaderVariableType Float;
	const static ShaderVariableType Vector2;
	const static ShaderVariableType Vector3;
	const static ShaderVariableType Vector4;
	const static ShaderVariableType Double;
	const static ShaderVariableType DVector2;
	const static ShaderVariableType DVector3;
	const static ShaderVariableType DVector4;
	const static ShaderVariableType Int;
	const static ShaderVariableType IVector2;
	const static ShaderVariableType IVector3;
	const static ShaderVariableType IVector4;
	const static ShaderVariableType UnsignedInt;
	const static ShaderVariableType UIVector2;
	const static ShaderVariableType UIVector3;
	const static ShaderVariableType UIVector4;
	const static ShaderVariableType Boolean;
	const static ShaderVariableType BVector2;
	const static ShaderVariableType BVector3;
	const static ShaderVariableType BVector4;
	const static ShaderVariableType Matrix;

	const static ShaderVariableType Sampler1D;
	const static ShaderVariableType Sampler2D;
	const static ShaderVariableType Sampler3D;
	const static ShaderVariableType SamplerCube;
	const static ShaderVariableType Sampler1DShadow;
	const static ShaderVariableType Sampler2DShadow;
	const static ShaderVariableType Sampler1DArray;
	const static ShaderVariableType Sampler2DArray;
	const static ShaderVariableType Sampler1DArrayShadow;
	const static ShaderVariableType Sampler2DArrayShadow;

	const static ShaderVariableType SamplerCubeArrayShadow;

	const static ShaderVariableType Sampler2DMultiSample;
	const static ShaderVariableType Sampler2DMultiSampleArray;
	const static ShaderVariableType SamplerCubeShadow;
	const static ShaderVariableType SamplerBuffer;
	const static ShaderVariableType Sampler2DRect;
	const static ShaderVariableType Sampler2DRectShadow;

	const static ShaderVariableType IntSampler1D;
	const static ShaderVariableType IntSampler2D;
	const static ShaderVariableType IntSampler3D;
	const static ShaderVariableType IntSamplerCube;
	const static ShaderVariableType IntSampler1DArray;
	const static ShaderVariableType IntSampler2DArray;
	const static ShaderVariableType IntSampler2DMultiSample;
	const static ShaderVariableType IntSampler2DMultiSampleArray;
	const static ShaderVariableType IntSamplerBuffer;
	const static ShaderVariableType IntSampler2DRect;

	const static ShaderVariableType UIntSampler1D;
	const static ShaderVariableType UIntSampler2D;
	const static ShaderVariableType UIntSampler3D;
	const static ShaderVariableType UIntSamplerCube;
	const static ShaderVariableType UIntSampler1DArray;
	const static ShaderVariableType UIntSampler2DArray;
	const static ShaderVariableType UIntSampler2DMultiSample;
	const static ShaderVariableType UIntSampler2DMultiSampleArray;
	const static ShaderVariableType UIntSamplerBuffer;
	const static ShaderVariableType UIntSampler2DRect;

	const static ShaderVariableType Image1D;
	const static ShaderVariableType Image2D;
	const static ShaderVariableType Image3D;
	const static ShaderVariableType Image2DRect;
	const static ShaderVariableType ImageCube;
	const static ShaderVariableType ImageBuffer;
	const static ShaderVariableType Image1DArray;
	const static ShaderVariableType Image2DArray;
	const static ShaderVariableType Image2DMultiSample;
	const static ShaderVariableType Image2DMultiSampleArray;

	const static ShaderVariableType IntImage1D;
	const static ShaderVariableType IntImage2D;
	const static ShaderVariableType IntImage3D;
	const static ShaderVariableType IntImage2DRect;
	const static ShaderVariableType IntImageCube;
	const static ShaderVariableType IntImageBuffer;
	const static ShaderVariableType IntImage1DArray;
	const static ShaderVariableType IntImage2DArray;
	const static ShaderVariableType IntImage2DMultiSample;
	const static ShaderVariableType IntImage2DMultiSampleArray;

	const static ShaderVariableType UIntImage1D;
	const static ShaderVariableType UIntImage2D;
	const static ShaderVariableType UIntImage3D;
	const static ShaderVariableType UIntImage2DRect;
	const static ShaderVariableType UIntImageCube;
	const static ShaderVariableType UIntImageBuffer;
	const static ShaderVariableType UIntImage1DArray;
	const static ShaderVariableType UIntImage2DArray;
	const static ShaderVariableType UIntImage2DMultiSample;
	const static ShaderVariableType UIntImage2DMultiSampleArray;

	const static ShaderVariableType Block;

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

	bool IsSampler() const;
	bool IsImage() const;
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