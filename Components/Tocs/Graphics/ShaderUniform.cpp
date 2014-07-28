#include "ShaderUniform.h"
#include "GLHeader.h"
#include <iostream>
#include "Shader.h"

//#define DEBUG_SHADER_UNIFORMS
//#define DUMMY_NOTIFICATIONS

using namespace std;
using namespace Tocs::Math;

namespace Tocs {
namespace Graphics {

ShaderUniform ShaderUniform::Dummy (nullptr,"Dummy",-1,ShaderVariableType::Int);

ShaderUniform::ShaderUniform(Shader *owningshader, string name, unsigned int location, const ShaderVariableType &type)
: Name(name)
, Location(location)
, Register(-1)
, Type(type)
, RType(none)
, OwningShader(owningshader)
{
}

ShaderUniform::ShaderUniform(Shader *owningshader, string name, unsigned int location, const ShaderVariableType &type, unsigned int reg)
: Name(name)
, Location(location)
, Register(reg)
, Type(type)
, RType(type.IsSampler() ? sampler : (type.IsImage() ? image : (type == ShaderVariableType::Block ? block : (type == ShaderVariableType::ShaderStorage ? storage : none))))
, OwningShader(owningshader)
{
}

ShaderUniform &ShaderUniform::operator = (const int &op2) 
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i (Location,op2);
	GLErrorCheck ();
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "Ui: " << Name << " : " << op2 << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const unsigned int &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1ui(Location, op2);
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "Ui: " << Name << " : " << op2 << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const float &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1f (Location,op2);
	GLErrorCheck ();
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "Uf: " << Name << " : " << op2 << endl;
#endif
	return *this;

}
ShaderUniform &ShaderUniform::operator = (const Texture2D &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i(Location, Register);
	GLErrorCheck();

	if (RType == sampler)
	{
		op2.Bind(Register);
	}
	else if (RType == image)
	{
		op2.BindImage(Register, 0);
	}
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name;
	if (RType == sampler)
		cout << " : tex(" << op2.GetID();
	else
		cout << " : img(" << op2.GetID();
	cout << ") @ " << Register << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const TextureArray &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i(Location, Register);
	GLErrorCheck();

	if (RType == sampler)
	{
		op2.Bind(Register);
	}
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name;
	if (RType == sampler)
		cout << " : tex(" << op2.GetID();
	else
		cout << " : img(" << op2.GetID();
	cout << ") @ " << Register << endl;
#endif
	return *this;
}
ShaderUniform &ShaderUniform::operator = (const DepthStencilBuffer &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i(Location, Register);
	GLErrorCheck();

	if (RType == sampler)
	{
		op2.Bind(Register);
	}
	//else if (RType == image)
	//{
	//	op2.BindImage(Register, 0);
	//}
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name;
	if (RType == sampler)
		cout << " : tex(" << op2.GetID();
	else
		cout << " : img(" << op2.GetID();
	cout << ") @ " << Register << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const CubeMapArray &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i(Location, Register);
	GLErrorCheck();

	if (RType == sampler)
	{
		op2.Bind(Register);
	}
	else if (RType == image)
	{
		//op2.BindImage(Register, 0);
	}
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name;
	if (RType == sampler)
		cout << " : texarr(" << op2.GetID();
	else
		cout << " : imgarr(" << op2.GetID();
	cout << ") @ " << Register << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator = (const Texture3D &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i (Location,Register);
	GLErrorCheck ();
	op2.Bind (Register);
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name << " : tex(" << op2.GetID() << ") @ " << Register << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const BufferTexture &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform1i (Location,Register);
	GLErrorCheck ();
	if (RType == sampler)
	{
		op2.Bind(Register);
	}
	else if (RType == image)
	{
		op2.BindImage(Register);
	}
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name;
	if (RType == sampler)
		cout << " : tex(" << op2.GetID();
	else
		cout << " : img(" << op2.GetID();
	cout << ") @ " << Register << endl;
#endif
	return *this;
}

ShaderUniform &ShaderUniform::BindVector2(const Math::Vector2*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform2fv(Location,count,reinterpret_cast<const float *>(vec));
	GLErrorCheck ();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

ShaderUniform &ShaderUniform::BindVector2(const Math::Vector2i*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform2iv(Location, count, reinterpret_cast<const int *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

ShaderUniform &ShaderUniform::BindVector2(const Math::Vector2ui*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform2uiv(Location, count, reinterpret_cast<const unsigned int *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

//////////////////////////

ShaderUniform &ShaderUniform::BindVector3(const Math::Vector3*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform3fv(Location, count, reinterpret_cast<const float *>(vec));
	GLErrorCheck();
	//cout << "U: " << Name << " : " << op2 << endl;
	return *this;
}

ShaderUniform &ShaderUniform::BindVector3(const Math::Vector3i*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform3iv(Location, count, reinterpret_cast<const int *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

ShaderUniform &ShaderUniform::BindVector3(const Math::Vector3ui*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform3uiv(Location, count, reinterpret_cast<const unsigned int *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

//////////////////////////

ShaderUniform &ShaderUniform::BindVector4(const Math::Vector4*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform4fv(Location, count, reinterpret_cast<const float *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

ShaderUniform &ShaderUniform::BindVector4(const Math::Vector4i*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform4iv(Location, count, reinterpret_cast<const int *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

ShaderUniform &ShaderUniform::BindVector4(const Math::Vector4ui*vec, int count)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	glUniform4uiv(Location, count, reinterpret_cast<const unsigned int *>(vec));
	GLErrorCheck();
#ifdef DEBUG_SHADER_UNIFORMS
	if (count == 1)
		cout << "U: " << Name << ": " << *vec;
	else
	{
		cout << "U: " << Name << ": [";
		for (int i = 0; i < count; ++i)
		{
			cout << vec[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "]" << endl;
	}
#endif
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Vector2 &op2)
{
	BindVector2(&op2, 1);
	return *this;
}
ShaderUniform &ShaderUniform::operator= (const Math::Vector2i &op2)
{
	BindVector2(&op2, 1);
	return *this;
}
ShaderUniform &ShaderUniform::operator= (const Math::Vector2ui &op2)
{
	BindVector2(&op2, 1);
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Vector3 &op2)
{
	BindVector3(&op2, 1);
	return *this;
}
ShaderUniform &ShaderUniform::operator= (const Math::Vector3i &op2)
{
	BindVector3(&op2, 1);
	return *this;
}
ShaderUniform &ShaderUniform::operator= (const Math::Vector3ui &op2)
{
	BindVector3(&op2, 1);
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Vector4 &op2)
{
	BindVector4(&op2, 1);
	return *this;
}
ShaderUniform &ShaderUniform::operator= (const Math::Vector4i &op2)
{
	BindVector4(&op2, 1);
	return *this;
}
ShaderUniform &ShaderUniform::operator= (const Math::Vector4ui &op2)
{
	BindVector4(&op2, 1);
	return *this;
}


ShaderUniform &ShaderUniform::operator = (const Matrix4 &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}
	glUniformMatrix4fv (Location,1,false,op2.GetData ());
	GLErrorCheck ();
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name << " : " << endl << op2 << endl;
#endif

	return *this;
}

ShaderUniform &ShaderUniform::operator= (const Math::Color &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}
#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name << " : (" << (int)op2.R << ", " << (int)op2.G << ", " << (int)op2.B << ")"  << endl;
#endif
	if (Type == ShaderVariableType::Vector4)
	{
		glUniform4f (Location,op2.R/255.0f,op2.G/255.0f,op2.B/255.0f,op2.A/255.0f);
		GLErrorCheck ();
	}
	else if (Type == ShaderVariableType::Vector3)
	{
		glUniform3f (Location,op2.R/255.0f,op2.G/255.0f,op2.B/255.0f);
		GLErrorCheck ();
	}
	return *this;
}

ShaderUniform &ShaderUniform::operator= (const BufferBase &op2)
{
	if (Location == -1)
	{
#ifdef DUMMY_NOTIFICATIONS
		cout << "Wrote to a Dummy Uniform" << endl;
#endif
		return *this;
	}

	if (!Type.IsBuffer())
	{
		cout << "Attempted to bind buffer to " << Type.ToString()  << std::endl;
		return *this;
	}

#ifdef DEBUG_SHADER_UNIFORMS
	cout << "U: " << Name << " : buff(" << op2.GetID() << ") @ " << Register << std::endl;
#endif
	if (RType == block)
		op2.BindTo (BufferTarget::Uniform, Register); 
	else if (RType == storage)
		op2.BindTo (BufferTarget::ShaderStorage, Register);
	return *this;
}
unsigned int ShaderUniform::BlockSize() const
{
	if (!IsBlock()) return 0;

	int result = 0;
	glGetActiveUniformBlockiv(OwningShader->GetID(), Location, GL_UNIFORM_BLOCK_DATA_SIZE, &result);
	GLErrorCheck();
	return result;
}



}}