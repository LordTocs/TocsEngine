#pragma once
#include "Texture.h"
#include "Texture3D.h"
#include "BufferTexture.h"
#include "DepthStencilBuffer.h"
#include "Buffer.h"
#include "CubeMapArray.h"
#include <string>
#include <Tocs/Math/Vector.h>
#include <Tocs/Math/Matrix4.h>
#include <Tocs/Math/Color.h>
#include "ShaderTypes.h"
namespace Tocs {
namespace Graphics {

class Shader;

class ShaderUniform
{
	enum RegisterType
	{
		image,
		sampler,
		block,
		none,
	};

	std::string Name;
	int Location;
	int Register; //Samplers, Blocks, or Images
	ShaderVariableType Type;
	Shader *OwningShader;
	RegisterType RType;

	ShaderUniform &BindVector2(const Math::Vector2*data, int count);
	ShaderUniform &BindVector2(const Math::Vector2i*data, int count);
	ShaderUniform &BindVector2(const Math::Vector2ui*data, int count);

	ShaderUniform &BindVector3(const Math::Vector3*data, int count);
	ShaderUniform &BindVector3(const Math::Vector3i*data, int count);
	ShaderUniform &BindVector3(const Math::Vector3ui*data, int count);

	ShaderUniform &BindVector4(const Math::Vector4*data, int count);
	ShaderUniform &BindVector4(const Math::Vector4i*data, int count);
	ShaderUniform &BindVector4(const Math::Vector4ui*data, int count);
public:
	ShaderUniform(Shader *owningShader, std::string name, unsigned int location, const ShaderVariableType &type);
	ShaderUniform(Shader *owningShader, std::string name, unsigned int location, const ShaderVariableType &type, unsigned int reg);

	ShaderUniform &operator= (const int &op2);
	ShaderUniform &operator= (const unsigned int &op2);
	ShaderUniform &operator= (const float &op2);

	ShaderUniform &operator= (const Texture2D &op2);
	ShaderUniform &operator= (const DepthStencilBuffer &op2);
	ShaderUniform &operator= (const Texture3D &op2);
	ShaderUniform &operator= (const BufferTexture &op2);
	ShaderUniform &operator= (const CubeMapArray &op2);

	ShaderUniform &operator= (const Math::Vector2 &op2);
	ShaderUniform &operator= (const Math::Vector2i &op2);
	ShaderUniform &operator= (const Math::Vector2ui &op2);

	ShaderUniform &operator= (const Math::Vector3 &op2);
	ShaderUniform &operator= (const Math::Vector3i &op2);
	ShaderUniform &operator= (const Math::Vector3ui &op2);

	ShaderUniform &operator= (const Math::Vector4 &op2);
	ShaderUniform &operator= (const Math::Vector4i &op2);
	ShaderUniform &operator= (const Math::Vector4ui &op2);

	ShaderUniform &operator= (const Math::Matrix4 &op2);
	ShaderUniform &operator= (const Math::Color &op2);
	ShaderUniform &operator= (const BufferBase &op2);

	//template<int n>
	//ShaderUniform &operator= (const Math::Vector3 (&op2) [n])
	//{
	//	return BindVector3(&op2[0],n);
	//}


	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector2(&op2)[n])
	{
		BindVector2(&op2[0], n);
	}

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector2i(&op2)[n])
	{
		BindVector2(&op2[0], n);
	}

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector2ui(&op2)[n])
	{
		BindVector2(&op2[0], n);
	}

	///

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector3 (&op2) [n])
	{
		BindVector3(&op2[0], n);
	}

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector3i(&op2)[n])
	{
		BindVector3(&op2[0], n);
	}

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector3ui(&op2)[n])
	{
		BindVector3(&op2[0], n);
	}

	///
	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector4(&op2)[n])
	{
		BindVector4(&op2[0], n);
	}

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector4i(&op2)[n])
	{
		BindVector4(&op2[0], n);
	}

	template <unsigned int n>
	ShaderUniform &operator= (const Math::Vector4ui(&op2)[n])
	{
		BindVector4(&op2[0], n);
	}

	//add more

	std::string GetName () const { return Name; }
	const ShaderVariableType &GetType () const { return Type; }
	int GetLocation () const { return Location; }
	int GetRegister () const { return Register; }
	bool IsBlock() const { return Type == ShaderVariableType::Block; }
	unsigned int BlockSize() const;

	friend class Shader;


	static ShaderUniform Dummy;

};

}}

