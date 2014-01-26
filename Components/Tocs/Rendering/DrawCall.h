#pragma once
#include <Tocs/Graphics/VAO.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/GraphicsContext.h>
#include <limits>

namespace Tocs {
namespace Rendering {

class DrawCall
{
	unsigned int Start;
	unsigned int Count;
	const unsigned int *Instances;
	const Graphics::VAO &VertexArray;
public:
	DrawCall(const Graphics::VAO &vertices, unsigned int start, unsigned int count)
		: Start(start), Count(count), Instances(nullptr),
		  VertexArray(vertices)
	{}

	DrawCall(const Graphics::VAO &vertices, unsigned int start, unsigned int count, const unsigned int *instances)
		: Start(start), Count(count), Instances(instances),
		VertexArray(vertices)
	{}

	void Execute (Graphics::GraphicsContext &context)
	{
		VertexArray.Bind();
		if (Instances == nullptr)
			context.DrawTriangles(Start,Count,VertexArray.GetFormat());
		else
			context.DrawTrianglesInstanced(Start, Count,*Instances, VertexArray.GetFormat());

		VertexArray.UnBind();
	}
};

}}

