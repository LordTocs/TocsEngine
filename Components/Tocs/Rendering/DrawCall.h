#pragma once
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Graphics/IBO.h>
#include <Tocs/Graphics/GraphicsContext.h>

namespace Tocs {
namespace Rendering {

class DrawCall
{
	unsigned int Start;
	unsigned int Count;
	const Graphics::VAO &VertexArray;
	const Graphics::IBO &Indices;
public:
	DrawCall(const Graphics::VAO &vertices, const Graphics::IBO &indices, unsigned int start, unsigned int count)
		: Start(start), Count(count),
		  VertexArray(vertices), Indices(indices)
	{}


	void Execute (Graphics::GraphicsContext &context)
	{
		VertexArray.Bind();
		Indices.Bind();
		context.DrawTriangles(Start,Count,Indices.GetFormat());
		Indices.UnBind();
		VertexArray.UnBind();
	}
};

}}

