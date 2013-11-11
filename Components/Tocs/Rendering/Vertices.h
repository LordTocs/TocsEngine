#pragma once
#include <Tocs/Math/Vector.h>
#include <Tocs/Graphics/VertexFormat.h>
#include <Tocs/Core/LateStatic.h>

namespace Tocs {
namespace Rendering {

class PositionTextureNormal
{
public:
	Math::Vector3 Position;
	Math::Vector2 TextureCoordinate;
	Math::Vector3 Normal;

	static Graphics::VertexFormat InitFormat ();
	static FirstUseStatic <Graphics::VertexFormat,&InitFormat> Format;

	PositionTextureNormal () {}

	PositionTextureNormal (const Math::Vector3 &pos, const Math::Vector2 &tex, const Math::Vector3 &norm)
		: Position (pos), TextureCoordinate(tex), Normal(norm) {}

	PositionTextureNormal &operator()(const Math::Vector3 &pos, const Math::Vector2 &tex, const Math::Vector3 &norm)
	{
		Position = pos;
		TextureCoordinate = tex;
		Normal = norm;
		return *this;
	}

	PositionTextureNormal &operator()(const Math::Vector3 &pos, const Math::Vector2 &tex)
	{
		Position = pos;
		TextureCoordinate = tex;
		return *this;
	}
};

class PositionTexture
{
public:
	Math::Vector3 Position;
	Math::Vector2 TextureCoordinate;

	static Graphics::VertexFormat InitFormat ();
	static FirstUseStatic <Graphics::VertexFormat,&InitFormat> Format;

	PositionTexture ()	{}

	PositionTexture(const Math::Vector3 &pos, const Math::Vector2 &tex)
		: Position (pos), TextureCoordinate(tex) {}

	PositionTexture &operator()(const Math::Vector3 &pos, const Math::Vector2 &tex)
	{
		Position = pos;
		TextureCoordinate = tex;
		return *this;
	}
};

class PositionOnly
{
public:
	Math::Vector3 Position;

	static Graphics::VertexFormat InitFormat ();
	static FirstUseStatic <Graphics::VertexFormat,&InitFormat> Format;

	PositionOnly () {}

	PositionOnly(const Math::Vector3 &pos)
		: Position (pos) {}

	PositionOnly &operator()(const Math::Vector3 &pos)
	{
		Position = pos;
		return *this;
	}
};

}}