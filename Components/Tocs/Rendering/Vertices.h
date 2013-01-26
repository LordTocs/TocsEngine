#pragma once
#include <Tocs/Math/Vector3.h>
#include <Tocs/Math/Vector2.h>
#include <Tocs/Graphics/VertexFormat.h>
namespace Tocs {
namespace Rendering {

class PositionTextureNormal
{
public:
	Math::Vector3 Position;
	Math::Vector2 TextureCoordinate;
	Math::Vector3 Normal;

	static Graphics::VertexFormat Format;

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

	static Graphics::VertexFormat Format;

	PositionTexture(const Math::Vector3 &pos, const Math::Vector2 &tex)
		: Position (pos), TextureCoordinate(tex) {}

	PositionTexture &operator()(const Math::Vector3 &pos, const Math::Vector2 &tex)
	{
		Position = pos;
		TextureCoordinate = tex;
		return *this;
	}
};

}}