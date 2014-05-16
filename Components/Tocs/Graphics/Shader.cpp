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
	  UniformsByName(std::move(moveme.UniformsByName))
{
	moveme.ID = 0;
	moveme._Linked = false;

	for (auto &i : UniformsByName) //shift all the uniforms to have a new owner.
	{
		i.second->OwningShader = this;
	}
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


void Shader::Link()
{
	//link
	glLinkProgram(ID);
	GLErrorCheck();
	int result = 0;
	//Check if it linked
	glGetObjectParameterivARB(ID, GL_LINK_STATUS, &result);
	GLErrorCheck();
	if (!result)
	{
		return;
	}

	//Check if its valid
	glGetObjectParameterivARB(ID, GL_VALIDATE_STATUS, &result);
	GLErrorCheck();
	if (!result)
	{
		return;
	}

	_Linked = true;
	
	int TextureRegister = 0;
	int ImageRegister = 0;

	int count;
	glGetProgramInterfaceiv(ID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &count);
	GLErrorCheck();
	const GLenum uniformprops[] = { GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION };
	for (int i = 0; i < count; ++i)
	{
		int values[sizeof(uniformprops) / sizeof(GLenum)];
		glGetProgramResourceiv(ID, GL_UNIFORM, i, sizeof(uniformprops) / sizeof(GLenum), uniformprops, sizeof(values) / sizeof(int), nullptr, values);
		GLErrorCheck();

		if (values[0] != -1)
			continue; //skip block variables

		std::vector<char> namedata(values[2]+1);
		glGetProgramResourceName(ID, GL_UNIFORM, i, namedata.size(), nullptr, &namedata[0]);
		GLErrorCheck();

		std::string name(namedata.begin(), namedata.end() - 1);

		Graphics::ShaderVariableType type = Graphics::ShaderVariableType::FromGLUniformType(values[1]);
		int reg = -1;
		if (type.IsSampler())
		{
			reg = TextureRegister++;
		}
		else if (type.IsImage())
		{
			reg = ImageRegister++;
		}

		UniformsByName.emplace(name,std::make_unique<ShaderUniform>(this,name,values[3],type,reg));
	}

	glGetProgramInterfaceiv(ID, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &count);
	GLErrorCheck();
	const GLenum blockprops[] = {GL_NAME_LENGTH, GL_BUFFER_BINDING };
	for (int i = 0; i < count; ++i)
	{
		int values[sizeof(blockprops) / sizeof(GLenum)];
		glGetProgramResourceiv(ID, GL_UNIFORM_BLOCK, i, sizeof(blockprops) / sizeof(GLenum), blockprops, sizeof(values) / sizeof(int), nullptr, values);
		GLErrorCheck();

		std::vector<char> namedata(values[0]+1);
		glGetProgramResourceName(ID, GL_UNIFORM_BLOCK, i, namedata.size(), nullptr, &namedata[0]);
		GLErrorCheck();

		std::string name(namedata.begin(), namedata.end() - 1);

		glUniformBlockBinding(ID, i, i);
		GLErrorCheck();

		UniformsByName.emplace(name, std::make_unique<ShaderUniform>(this, name, i, Graphics::ShaderVariableType::Block, i));
	}

	glGetProgramInterfaceiv(ID, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &count);
	GLErrorCheck();
	const GLenum shaderprops[] = { GL_NAME_LENGTH, GL_BUFFER_BINDING };
	for (int i = 0; i < count; ++i)
	{
		int values[sizeof(shaderprops) / sizeof(GLenum)];
		glGetProgramResourceiv(ID, GL_SHADER_STORAGE_BLOCK, i, sizeof(shaderprops) / sizeof(GLenum), shaderprops, sizeof(values) / sizeof(int), nullptr, values);
		GLErrorCheck();

		std::vector<char> namedata(values[0]+1);
		glGetProgramResourceName(ID, GL_SHADER_STORAGE_BLOCK, i, namedata.size(), nullptr, &namedata[0]);
		GLErrorCheck();
		std::string name(namedata.begin(), namedata.end() - 1);


		UniformsByName.emplace(name,std::make_unique<ShaderUniform>(this, name, values[1], Graphics::ShaderVariableType::Block, values[1]));
	}
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
	for (auto i = UniformsByName.begin (); i != UniformsByName.end (); ++i)
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