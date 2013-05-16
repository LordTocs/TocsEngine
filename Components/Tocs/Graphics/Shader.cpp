#include "Shader.h"
#include "GLHeader.h"
#include <Tocs/Core/Tokenizer.h>
using namespace std;

namespace Tocs {
namespace Graphics {

Shader::Shader(void)
	: ID (glCreateProgram ()),
	  _Linked (false)
{
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

	int result = 0;
	//Check if it linked
	glGetObjectParameterivARB (ID, GL_LINK_STATUS, &result);
	GLErrorCheck ();
	if (!result)
		return;

	//Check if its valid
	glGetObjectParameterivARB (ID, GL_VALIDATE_STATUS, &result);
	GLErrorCheck ();
	if (!result)
		return;

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

	for (int i = 0; i < uniformcount; ++i)
	{
		memset (tempname,0,500);
		glGetActiveUniform (ID,i,500,&namelen,&size,&type,tempname);
		GLErrorCheck ();
		ShaderUniform *uniform = nullptr;
		if (type == GL_SAMPLER_2D || type == GL_SAMPLER_2D_ARRAY || type == GL_SAMPLER_3D)
		{
			uniform = new ShaderUniform (tempname,glGetUniformLocation (ID,tempname),ShaderVariableType::FromGLUniformType (type),TextureRegister);
			++TextureRegister;
		}
		else
		{
			uniform = new ShaderUniform (tempname,glGetUniformLocation (ID,tempname),ShaderVariableType::FromGLUniformType (type));
		}

		UniformsByName[uniform->GetName ()] = uniform;
		UniformsByLocation[uniform->GetLocation ()] = uniform;
	}
}

ShaderUniform &Shader::operator [] (string name)
{
	auto i = UniformsByName.find(name);
	if (i == UniformsByName.end())
	{
		std::cout << "U: " << name << std::endl;
		return ShaderUniform::Dummy;
	}
	return *(*i).second;
}
ShaderUniform &Shader::operator [] (int address)
{
	auto i = UniformsByLocation.find(address);
	if (i == UniformsByLocation.end())
	{
		std::cout << "U: " << address << std::endl;
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
	cout << "Linked: " << out << endl;
	glGetProgramiv(ID,GL_ACTIVE_UNIFORMS,&out);
	cout << "------------" << endl
		 << "Uniforms: " << out << endl;
	for (auto i = UniformsByLocation.begin (); i != UniformsByLocation.end (); ++i)
	{
		cout << (*i).first << ": " << (*i).second->GetType ().ToString () << " " << (*i).second->GetName () << " " << (*i).second->GetTextureRegister () << endl;
	}
	glGetProgramiv(ID,GL_ACTIVE_ATTRIBUTES,&out);
	cout << "------------" << endl
		 << "Attributes: " << out << endl;
	
	for (int i = 0; i < out; ++i)
	{
		char name [255];
		unsigned int type = 0;
		int size = 0;
		int nmlen = 0;
		glGetActiveAttrib(ID,i,255,&nmlen,&size,&type,&name[0]);
		cout << glGetAttribLocation (ID,name) << ": " << ShaderVariableType::FromGLUniformType(type).ToString () << " " << name << " " << size << endl;
	}
	cout << endl;
}

}}