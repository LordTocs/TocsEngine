#pragma once
#include "Shader.h"

namespace Tocs {
namespace Graphics {


class ShaderUniformSet
{
	class IProperty
	{
		unsigned int Offset;

	public:
		virtual void Set (Shader &shader) = 0;
	};

	template <class T>
	class Property : public IProperty
	{
		T Value;
	};

public:
	ShaderUniformSet(void);
	~ShaderUniformSet(void);
};

}}
