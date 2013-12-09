#pragma once
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/GraphicsContext.h>

namespace Tocs {
namespace Rendering {

class DrawCall
{
	unsigned int Start;
	unsigned int Count;
	const Graphics::VAO &VertexArray;
public:
	DrawCall(const Graphics::VAO &vertices, unsigned int start, unsigned int count)
		: Start(start), Count(count),
		  VertexArray(vertices)
	{}


	void Execute (Graphics::GraphicsContext &context)
	{
		VertexArray.Bind();
		context.DrawTriangles(Start,Count,VertexArray.GetFormat());
		VertexArray.UnBind();
	}
};

}}

