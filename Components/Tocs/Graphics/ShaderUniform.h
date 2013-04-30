#pragma once
#include "Texture.h"
#include "Texture3D.h"
#include <string>
#include <Tocs/Math/Vector3.h>
#include <Tocs/Math/Matrix4.h>
#include <Tocs/Math/Color.h>
#include "ShaderTypes.h"
namespace Tocs {
namespace Graphics {

class ShaderUniform
{
	std::string Name;
	int Location;
	int TextureRegister; //Samplers Only
	ShaderVariableType Type;
public:
	ShaderUniform(std::string name, unsigned int location, const ShaderVariableType &type);
	ShaderUniform(std::string name, unsigned int location, const ShaderVariableType &type, unsigned int texture);

	ShaderUniform &operator= (const int &op2);
	ShaderUniform &operator= (const float &op2);
	ShaderUniform &operator= (const Texture2D &op2);
	ShaderUniform &operator= (const Texture3D &op2);
	ShaderUniform &operator= (const Math::Vector3 &op2);
	ShaderUniform &operator= (const Math::Matrix4 &op2);
	ShaderUniform &operator= (const Math::Color &op2);
	//add more

	std::string GetName () const { return Name; }
	const ShaderVariableType &GetType () const { return Type; }
	int GetLocation () const { return Location; }
	int GetTextureRegister () const { return TextureRegister; }

};

}}

