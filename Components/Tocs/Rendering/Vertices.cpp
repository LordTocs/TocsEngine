#include "Vertices.h"
#include <Tocs/Core/StaticInitializer.h>
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

	FirstUseStatic <Graphics::VertexFormat, &PositionTextureNormalTangent::InitFormat> PositionTextureNormalTangent::Format;

Graphics::VertexFormat PositionTextureNormalTangent::InitFormat()
{
	Graphics::VertexFormat format;
	format.AddMember("Position", GPUType::Vector3, false);
	format.AddMember("TextureCoordinate", GPUType::Vector2, false);
	format.AddMember("Normal", GPUType::Vector3, true);
	format.AddMember("Tangent", GPUType::Vector3, true);
	return format;
}



FirstUseStatic <Graphics::VertexFormat,&PositionTextureNormal::InitFormat> PositionTextureNormal::Format;

Graphics::VertexFormat PositionTextureNormal::InitFormat ()
{
	Graphics::VertexFormat format;
	format.AddMember ("Position", GPUType::Vector3, false);
	format.AddMember("TextureCoordinate", GPUType::Vector2, false);
	format.AddMember("Normal", GPUType::Vector3, true);
	return format;
}

FirstUseStatic <Graphics::VertexFormat,&PositionTexture::InitFormat> PositionTexture::Format;

Graphics::VertexFormat PositionTexture::InitFormat ()
{
	Graphics::VertexFormat format;
	format.AddMember("Position", GPUType::Vector3, false);
	format.AddMember("TextureCoordinate", GPUType::Vector2, false);
	return format;
}

FirstUseStatic <Graphics::VertexFormat,&PositionOnly::InitFormat> PositionOnly::Format;

Graphics::VertexFormat PositionOnly::InitFormat ()
{
	Graphics::VertexFormat format;
	format.AddMember("Position", GPUType::Vector3, false);
	return format;
}

}}