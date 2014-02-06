#include "Shader.h"
#include "GLHeader.h"
#include <Tocs/Core/Tokenizer.h>
#include <cassert>
using namespace std;

namespace Tocs {
namespace Graphics {

Shader::Shader(void)
	: ID (glCreateProgram ()),
	  _Linked (false)
{
	GLErrorCheck();
	//Bind ();
	//UnBind ();
}

Shader::Shader (Shader &&moveme)
	: ID (moveme.ID),
	  _Linked (moveme._Linked),
	  UniformsByLocation(std::move(moveme.UniformsByLocation)),
	  UniformsByName(std::move(moveme.UniformsByName))
{
	moveme.ID = 0;
	moveme._Linked = false;
}

Shader::~Shader(void)
{
	glDeleteProgram (ID);
	GLErrorCheck();
}

void Shader::AddCode (const ShaderCode &code)
{
	glAttachShader (ID,code.GetID ());
	GLErrorCheck ();
}

void Shader::Link ()
{
	//link
	glLinkProgram (ID);
	GLErrorCheck();
	int result = 0;
	//Check if it linked
	glGetObjectParameterivARB (ID, GL_LINK_STATUS, &result);
	GLErrorCheck ();
	if (!result)
	{
		return;
	}

	//Check if its valid
	glGetObjectParameterivARB (ID, GL_VALIDATE_STATUS, &result);
	GLErrorCheck ();
	if (!result)
	{
		return;
	}

	_Linked = true;
	int uniformcount = 0;
	glGetObjectParameterivARB (ID, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &uniformcount);
	GLErrorCheck ();
	//Build uniform table
	char tempname [500];
	int namelen = 0;
	int size = 0;
	GLenum type;
	int TextureRegister = 0;
	int ImageRegister = 0;

	for (int i = 0; i < uniformcount; ++i)
	{
		memset (tempname,0,500);
		glGetActiveUniform (ID,i,500,&namelen,&size,&type,tempname);
		GLErrorCheck ();
		ShaderUniform *uniform = nullptr;

		ShaderVariableType stype = ShaderVariableType::FromGLUniformType(type);
		unsigned int location = glGetUniformLocation(ID, tempname);
		GLErrorCheck();
		if (stype.IsSampler())
		{
			uniform = new ShaderUniform(this, tempname, location, stype, TextureRegister++);
		}
		else if (stype.IsImage())
		{
			uniform = new ShaderUniform(this, tempname, location, stype, ImageRegister++);
		}
		else
		{
			uniform = new ShaderUniform(this, tempname, location, stype);
		}

		UniformsByName[uniform->GetName ()] = uniform;
		UniformsByLocation[uniform->GetLocation ()] = uniform;
	}

	GLint numBlocks;
	glGetProgramiv(ID, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);
	GLErrorCheck();

	for(int blockIx = 0; blockIx < numBlocks; ++blockIx)
	{
		GLint nameLen;
		glGetActiveUniformBlockiv(ID, blockIx, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLen);
		GLErrorCheck();
		std::vector<GLchar> vname; //Yes, not std::string. There's a reason for that.
		vname.resize(nameLen);
		glGetActiveUniformBlockName(ID, blockIx, nameLen, NULL, &vname[0]);
		GLErrorCheck();
		ShaderUniform *uniform = nullptr;
		std::string name (vname.begin(), vname.end() - 1);

		uniform = new ShaderUniform (this,name,blockIx,ShaderVariableType::Block,blockIx);
		glUniformBlockBinding(ID, blockIx, blockIx);
		GLErrorCheck();
		std::cout << "Block: " << uniform->GetName() << " : " << uniform->BlockSize() << " bytes" << std::endl;

		//std::cout << "glUniformBlockBinding(" << ID << ", " << blockIx << ", " << blockIx << ")" << endl;
		UniformsByName[uniform->GetName ()] = uniform;
		UniformsByLocation[uniform->GetLocation ()] = uniform;
	}

	GLint numBuffers;

}

ShaderUniform &Shader::operator [] (string name)
{
	auto i = UniformsByName.find(name);
	if (i == UniformsByName.end())
	{
		//std::cout << "Returning Dummy Uniform For: " << name << std::endl;
		return ShaderUniform::Dummy;
	}
	return *(*i).second;
}
ShaderUniform &Shader::operator [] (int address)
{
	auto i = UniformsByLocation.find(address);
	if (i == UniformsByLocation.end())
	{
		//std::cout << "Returning Dummy Uniform For: " << address << std::endl;
		return ShaderUniform::Dummy;
	}
	return *(*i).second;
}

void Shader::Bind ()
{
	glUseProgram (ID);
	GLErrorCheck ();
}

void Shader::UnBind ()
{
	glUseProgram(0);
	GLErrorCheck ();
}

string Shader::GetLinkErrors ()
{
	int loglen;
	glGetProgramiv(ID,GL_INFO_LOG_LENGTH,&loglen);
	GLErrorCheck ();
	if (loglen == 0)
		return "No Errors.";

	string result;
	int resultlen;
	result.resize (loglen);
	glGetProgramInfoLog (ID,loglen,&resultlen,&result[0]);
	GLErrorCheck ();
	return result;
}

void Shader::SetAttribute (std::string attribute, int index)
{
	glBindAttribLocation (ID,index,attribute.c_str ());
	GLErrorCheck ();
}
int Shader::GetAttribute (std::string attribute) const
{
	return glGetAttribLocation (ID,attribute.c_str ());
}
int Shader::GetOutput (std::string output) const
{
	return glGetFragDataLocation (ID,output.c_str ());
}
void Shader::SetOutput (std::string output, int index)
{
	glBindFragDataLocation (ID,index,output.c_str ());
	GLErrorCheck ();
}

unsigned int Shader::GetWorkgroupSize() const
{
	int result = 0;
	glGetProgramiv(ID, GL_COMPUTE_WORK_GROUP_SIZE, &result);
	GLErrorCheck();

	return result;
}

static std::string StripQuotes (const std::string &token)
{
	return token.substr (1,token.length () - 2);
}

Shader Shader::LoadFromFile (const std::string &filename)
{
	Lexing::StringSource source = Lexing::StringSource::FromFile(filename);
	Lexing::Tokenizer tokens (source);

	Shader result;

	while (!tokens.EndOfStream ())
	{
		std::string type = tokens.GetToken ();

		if (type == "vert")
		{
			if (!tokens.Is (":"))
				break;

			ShaderCode code (ShaderType::Vertex);
			std::string codefile = StripQuotes (tokens.GetToken ());
			code.CompileFromFile (codefile); //Need to use Asset system.
			if (!code.Compiled ())
			{
				cout << "CompileErrors (" << codefile << "):" << endl 
					 << code.GetCompileErrors ()  << endl << endl;
				assert(false);
			}
			result.AddCode (code);
		}
		else if (type == "frag")
		{
			if (!tokens.Is (":"))
				break;

			ShaderCode code (ShaderType::Pixel);
			std::string codefile = StripQuotes (tokens.GetToken ());
			code.CompileFromFile (codefile);
			if (!code.Compiled ())
			{
				cout << "CompileErrors (" << codefile << "):" << endl
				     << code.GetCompileErrors () << endl << endl;
				assert(false);
			}
			result.AddCode (code);
		}
	}

	result.Link ();
	if (!result.Linked ())
	{
		cout << "Link Errors (" << filename << "):" << endl;
		cout << result.GetLinkErrors () << endl;
	}

	return result;

}

void Shader::PrintDebugInformation () const
{
	cout << "ShaderInfo: " << endl;
	int out;
	glGetProgramiv(ID,GL_LINK_STATUS,&out);
	GLErrorCheck();
	cout << "Linked: " << out << endl;
	glGetProgramiv(ID,GL_ACTIVE_UNIFORMS,&out);
	GLErrorCheck();
	cout << "------------" << endl
		 << "Uniforms: " << out << endl;
	for (auto i = UniformsByLocation.begin (); i != UniformsByLocation.end (); ++i)
	{
		cout << (*i).first << ": " << (*i).second->GetType ().ToString () << " " << (*i).second->GetName () << " " << (*i).second->GetRegister () << endl;
	}
	glGetProgramiv(ID,GL_ACTIVE_ATTRIBUTES,&out);
	GLErrorCheck();
	cout << "------------" << endl
		 << "Attributes: " << out << endl;
	
	for (int i = 0; i < out; ++i)
	{
		char name [255];
		unsigned int type = 0;
		int size = 0;
		int nmlen = 0;
		glGetActiveAttrib(ID,i,255,&nmlen,&size,&type,&name[0]);
		GLErrorCheck();
		cout << glGetAttribLocation (ID,name) << ": " << ShaderVariableType::FromGLUniformType(type).ToString () << " " << name << " " << size << endl;
		GLErrorCheck();
	}

	
	GLint numBuffers = 0;
	glGetProgramInterfaceiv(ID, GL_BUFFER_VARIABLE, GL_ACTIVE_RESOURCES, &numBuffers);
	GLErrorCheck();
	cout << "------------" << endl
		<< "Buffer Variables: " << numBuffers << endl;
	static const GLenum bufferprops[] = { GL_NAME_LENGTH, GL_OFFSET, GL_TYPE, GL_TOP_LEVEL_ARRAY_SIZE, GL_TOP_LEVEL_ARRAY_STRIDE};
	for (int i = 0; i < numBuffers; ++i)
	{
		GLint values[sizeof(bufferprops) / sizeof(GLenum)];
		glGetProgramResourceiv(ID, GL_BUFFER_VARIABLE, i, sizeof(bufferprops) / sizeof(GLenum), bufferprops, sizeof(bufferprops) / sizeof(GLenum), nullptr, values);
		GLErrorCheck();

		std::vector<char> nameData(values[0]);
		glGetProgramResourceName(ID, GL_BUFFER_VARIABLE, i, nameData.size(), NULL, &nameData[0]);
		GLErrorCheck();
		std::string name(nameData.begin(), nameData.end() - 1);

		std::cout << name << ": Offset(" << values[1] << ") " << Graphics::ShaderVariableType::FromGLUniformType(values[2]).ToGLSLTypeString() << " ArrSize(" << values[3] << ") ArrStride(" << values[4] << ")" << std::endl;
	}

	cout << endl;
}

}}