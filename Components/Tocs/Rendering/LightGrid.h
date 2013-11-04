#pragma once
#include <Tocs/Math/Vector4.h>
#include <Tocs/Math/Vector4i.h>
#include <Tocs/Math/Vector3.h>
#include <Tocs/Math/Vector2.h>
#include <Tocs/Math/Vector2i.h>
#include <Tocs/Graphics/Buffer.h>
#include <Tocs/Graphics/BufferTexture.h>
#include "Camera.h"
#include "Light.h"
#include <vector>
#include <memory>

namespace Tocs {
namespace Rendering {

#define LIGHT_GRID_TILE_DIM_X 32
#define LIGHT_GRID_TILE_DIM_Y 32

// Max screen size of 1920x1080
#define LIGHT_GRID_MAX_DIM_X ((1920 + LIGHT_GRID_TILE_DIM_X - 1) / LIGHT_GRID_TILE_DIM_X)
#define LIGHT_GRID_MAX_DIM_Y ((1080 + LIGHT_GRID_TILE_DIM_Y - 1) / LIGHT_GRID_TILE_DIM_Y)


class LightGrid
{
	std::unique_ptr<Math::Vector2i []> CountsAndOffsetsCPU;
	std::vector<int> LightIndexListsCPU;

	Math::Vector2i &CountsAndOffsets (int x, int y) { return CountsAndOffsetsCPU[ x + y * LIGHT_GRID_MAX_DIM_X]; }

	Graphics::Buffer<Math::Vector2i> Grid;

	Graphics::Buffer<int> LightIndexLists;
	Graphics::BufferTexture LightIndexListsTexture;

	Graphics::Buffer<Math::Vector4> PositionRange;
	Graphics::Buffer<Math::Vector4> ColorBuffer;

	unsigned int TileSize;
	Math::Vector2i GridSize;
public:
	LightGrid();

	void Configure (const Camera &camera, const std::vector<Light *> &lights);
};

}}