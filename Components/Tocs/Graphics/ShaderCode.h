#pragma once
#include <string>
#include "ShaderTypes.h"
namespace Tocs {
namespace Graphics {

class ShaderCode
{
	int ID;
	ShaderCode (const ShaderCode &);
public:
	friend class Shader;

	ShaderCode(ShaderType type);
	~ShaderCode();
	ShaderCode(ShaderCode && copyme);

	int GetID () const { return ID; }

	bool Compiled () const;

	std::string GetCompileErrors ();
	void Compile (const std::string &code);
	void CompileFromFile (const std::string &file);

	ShaderType GetType ();

	bool operator < (const ShaderCode &op2) const //For sorting...
	{
		return GetID () < op2.GetID ();
	}

	static ShaderCode LoadFromFile (const std::string &filename);
};

}}
