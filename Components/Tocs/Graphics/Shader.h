 #pragma once
#include <map>
#include <string>
#include <memory>
#include "ShaderCode.h"
#include "ShaderUniform.h"


namespace Tocs {
namespace Graphics {

class Shader
{
	unsigned int ID;
	std::map <std::string, std::unique_ptr<ShaderUniform>> UniformsByName;

	

	bool _Linked;
public:
	Shader();
	Shader(Shader &&moveme);
	~Shader();

	Shader(const Shader &) = delete;
	Shader &operator=(const Shader &) = delete;

	void Link ();
	bool Linked () const {return _Linked;}

	void AddCode (const ShaderCode &code);

	std::string GetLinkErrors ();

	void Bind ();
	void UnBind();

	unsigned int GetID () const { return ID; }

	int GetLocation (std::string uniform) const;
	
	void SetAttribute (std::string attribute, int index);
	int GetAttribute (std::string attribute) const;

	int GetOutput (std::string output) const;
	void SetOutput (std::string output, int index);

	ShaderUniform &operator [] (std::string name);

	static Shader LoadFromFile (const std::string &filename);

	void PrintDebugInformation () const;

	unsigned int GetWorkgroupSize() const;
	
};

}}

