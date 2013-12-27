#include "DebugDraw.h"
#include <Tocs/Core/Asset.h>
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Core/LateStatic.h>
namespace Tocs {
namespace Rendering {


std::vector<DebugDraw::Segment> DebugDraw::Lines;


void DebugDraw::Line(const Math::Vector3 &a, const Math::Vector3 &b)
{
	Lines.emplace_back(a, b, Math::Color(255,255,255));
}
void DebugDraw::Line(const Math::Vector3 &a, const Math::Vector3 &b, Math::Color color)
{
	Lines.emplace_back(a, b, color);
}

Graphics::Buffer<Math::Vector3> GenLineBuffer()
{
	return Graphics::Buffer<Math::Vector3>(2);
}

static FirstUseStatic <Graphics::Buffer<Math::Vector3>, GenLineBuffer> LineVertices;


Graphics::VAO BuildLineVAO()
{
	static Graphics::Buffer<unsigned int> inds(2);
	Graphics::VertexFormat fmt;
	fmt.AddMember("Pos", Graphics::VertexType::Vec3);

	inds.Write({ 0, 1 });

	Graphics::VAO result;
	result.Bind();
	result.AddVBO(LineVertices.Get(), fmt);
	result.AddIBO(inds);
	result.UnBind();
	return result;
}


static FirstUseStatic<Graphics::VAO, BuildLineVAO> LineVAO;


void DebugDraw::Draw(Graphics::GraphicsContext &context, const Camera &cam)
{
	static Asset<Graphics::Shader> lineshader = Asset<Graphics::Shader>::Load("solid.shd");

	lineshader.Get().Bind();
	
	lineshader.Get()["View"] = cam.GetView();
	lineshader.Get()["Projection"] = cam.GetProjection();
	lineshader.Get()["World"] = Math::Matrix4::Identity;
	for (auto &s : Lines)
	{
		lineshader.Get()["Color"] = s.color;
		LineVertices.Get().Write({ s.a, s.b });
		LineVAO.Get().Bind();
		context.DrawLines(1);
		LineVAO.Get().UnBind();
	}
	
	lineshader.Get().UnBind();
}

void DebugDraw::Clear()
{
	Lines.clear();
}

}
}