#include "Vertices.h"
#include <Tocs/Core/StaticInitializer.h>
using namespace Tocs::Graphics;

namespace Tocs {
namespace Rendering {

Graphics::VertexFormat PositionTextureNormal::Format;

static void InitPTN ()
{
	PositionTextureNormal::Format.AddMember ("Position",VertexType::Vec3,false);
	PositionTextureNormal::Format.AddMember ("TextureCoordinate",VertexType::Vec2,false);
	PositionTextureNormal::Format.AddMember ("Normal",VertexType::Vec3,true);
}

StaticInitializer initptn (&InitPTN);

Graphics::VertexFormat PositionTexture::Format;

static void InitPT ()
{
	PositionTexture::Format.AddMember ("Position",VertexType::Vec3,false);
	PositionTexture::Format.AddMember ("TextureCoordinate",VertexType::Vec2,false);
}

StaticInitializer initpt (&InitPT);

}}