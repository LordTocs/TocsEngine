#pragma once
#include <map>
#include <string>

#include "ShaderCode.h"
#include "ShaderUniform.h"


namespace Tocs {
namespace Graphics {

class Shader
{
	unsigned int ID;
	std::map <std::string, ShaderUniform *> UniformsByName;
	std::map <int, ShaderUniform *> UniformsByLocation;

	Shader (const Shader &); //No copying shaders

	bool _Linked;
public:
	Shader();
	Shader(Shader &&moveme);
	~Shader();

	void Link ();
	bool Linked () const {return _Linked;}

	void AddCode (const ShaderCode &code);

	std::string GetLinkErrors ();

	void Bind ();
	void UnBind();

	int GetLocation (std::string uniform) const;
	
	void SetAttribute (std::string attribute, int index);
	int GetAttribute (std::string attribute) const;

	int GetOutput (std::string output) const;
	void SetOutput (std::string output, int index);

	ShaderUniform &operator [] (std::string name);
	ShaderUniform &operator [] (int address);

	static Shader LoadFromFile (const std::string &filename);

	void PrintDebugInformation () const;
	
};

}}

