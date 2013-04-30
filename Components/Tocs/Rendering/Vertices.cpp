#include "Vertices.h"
#include <Tocs/Core/StaticInitializer.h>
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

FirstUseStatic <Graphics::VertexFormat,&PositionTextureNormal::InitFormat> PositionTextureNormal::Format;

Graphics::VertexFormat PositionTextureNormal::InitFormat ()
{
	Graphics::VertexFormat format;
	format.AddMember ("Position", VertexType::Vec3, false);
	format.AddMember ("TextureCoordinate", VertexType::Vec2, false);
	format.AddMember ("Normal", VertexType::Vec3, true);
	return format;
}

FirstUseStatic <Graphics::VertexFormat,&PositionTexture::InitFormat> PositionTexture::Format;

Graphics::VertexFormat PositionTexture::InitFormat ()
{
	Graphics::VertexFormat format;
	format.AddMember ("Position",VertexType::Vec3, false);
	format.AddMember ("TextureCoordinate",VertexType::Vec2, false);
	return format;
}

FirstUseStatic <Graphics::VertexFormat,&PositionOnly::InitFormat> PositionOnly::Format;

Graphics::VertexFormat PositionOnly::InitFormat ()
{
	Graphics::VertexFormat format;
	format.AddMember ("Position",VertexType::Vec3,false);
	return format;
}

}}