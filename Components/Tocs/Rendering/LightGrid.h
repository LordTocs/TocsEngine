#pragma once
#include <Tocs/Math/Vector.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/BufferTexture.h>
#include <Tocs/Graphics/UniformMap.h>
#include "Camera.h"
#include "Light.h"
#include <vector>
#include <memory>

namespace Tocs {
namespace Rendering {


class LightGrid
{
	unsigned int TileSize;
	Math::Vector2i MaxGridSize;
	Math::Vector2i GridSize;

	std::unique_ptr<Math::Vector4i []> CountsAndOffsetsCPU;
	std::vector<int> LightIndexListsCPU;

	Math::Vector4i &CountsAndOffsets (int x, int y) { return CountsAndOffsetsCPU[ x + y * GridSize.X]; }

	Graphics::Buffer<Math::Vector4i> Grid; //UBO

	Graphics::Buffer<int> LightIndexLists; //TBO
	Graphics::BufferTexture LightIndexListsTexture;

	Graphics::Buffer<Math::Vector4> PositionRange; //UBO
	Graphics::Buffer<Math::Vector4> ColorBuffer; //UBO

	Graphics::UniformMap Inputs;
public:
	LightGrid();

	void Configure (const Camera &camera, const std::vector<Light *> &lights);

	const Graphics::UniformMap &GetShaderInputs() const { return Inputs; }
};

}}