#pragma once
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Texture.h>
#include <Tocs/Math/Color.h>
#include <Tocs/Graphics/Shader.h>
namespace Tocs{
namespace Rendering{

class MaterialValueType
{
	enum InternalFormat
	{
		constant,
		map,
		mapcomponent
	};
	InternalFormat Internal;

	MaterialValueType (InternalFormat format)
		: Internal (format) {}

public:
	const static MaterialValueType Constant;
	const static MaterialValueType Map;
	const static MaterialValueType MapComponent;

	bool operator ==  (const MaterialValueType &op2) const {return Internal == op2.Internal;}
	bool operator !=  (const MaterialValueType &op2) const {return Internal != op2.Internal;}
	bool operator < (const MaterialValueType &op2) const { return Internal < op2.Internal; }
};

}}