#include "LightGrid.h"
#include <algorithm>
#include "DebugDraw.h"

namespace Tocs {
namespace Rendering {


static void UpdateClipRegionRoot (float nc, float lc, float lz, float radius, float camerascale, float &clipmin, float &clipmax)
{
	float nz = (radius - nc * lc) / lz;
	float pz = (lc * lc + lz * lz - radius * radius) / (lz - (nz / nc) * lc);

	if (pz < 0.0f) 
	{
		float c = -nz * camerascale / nc;
		if (nc < 0.0f) 
		{        
			// Left side boundary
			clipmin = std::max(clipmin, c);
		} 
		else 
		{   
			// Right side boundary
			clipmax = std::min(clipmax, c);
		}
	}
}

static void UpdateClipRegion (float lc, float lz, float radius, float camerascale, float &clipmin, float &clipmax)
{
	float rSq = radius * radius;
	float lcSqPluslzSq = lc * lc + lz * lz;
	float d = rSq * lc * lc - lcSqPluslzSq * (rSq - lz * lz);

	if (d >= 0.0f) 
	{
		float a = radius * lc;
		float b = sqrt(d);
		float nx0 = (a + b) / lcSqPluslzSq;
		float nx1 = (a - b) / lcSqPluslzSq;

		UpdateClipRegionRoot(nx0, lc, lz, radius, camerascale, clipmin, clipmax);
		UpdateClipRegionRoot(nx1, lc, lz, radius, camerascale, clipmin, clipmax);
	}
}

//Computes a clipspace bounding box of a sphere.
static Math::Vector4 ComputeClipRegion (Math::Vector3 pos, float radius, float cnear,const Math::Matrix4 &projection)
{
	Math::Vector4 region (1.0f,1.0f,-1.0f,-1.0f);
	if (pos.Z - radius <= -cnear) //In front of the camera?
	{
		Math::Vector2 clipmin(-1.0f, -1.0f);
		Math::Vector2 clipmax( 1.0f,  1.0f);

		UpdateClipRegion (pos.X,pos.Z,radius,projection(0,0),clipmin.X,clipmax.X);
		UpdateClipRegion (pos.Y,pos.Z,radius,projection(1,1),clipmin.Y,clipmax.Y);

		region(clipmin.X,clipmin.Y,clipmax.X,clipmax.Y);
	}

	return region;
}

static Math::Vector4i ClipToScreenSpace (Math::Vector4 cliprect, const Camera &camera)
{
	cliprect *= -1;

	std::swap (cliprect.X, cliprect.Z);
	std::swap (cliprect.Y, cliprect.W);

	//(maxx,maxy,minx,miny)

	cliprect *= 0.5f;
	cliprect += Math::Vector4 (0.5f,0.5f,0.5f,0.5f);


	static const Math::Vector4 zeros (0.0f,0.0f,0.0f,0.0f);
	static const Math::Vector4 ones (1.0f,1.0f,1.0f,1.0f);

	cliprect = Clamp (cliprect,zeros,ones);

	Math::Vector4i result;
	result.X = int(cliprect.X * float(camera.Width));
	result.Y = int(cliprect.Y * float(camera.Height));
	result.Z = int(cliprect.Z * float(camera.Width));
	result.W = int(cliprect.W * float(camera.Height));

	return result;

}


LightGrid::LightGrid()
: TileSize(32)
, MaxGridSize((1920 + TileSize - 1) / TileSize, (1080 + TileSize - 1) / TileSize)
, GridSize(MaxGridSize)
, CountsAndOffsetsCPU(new Math::Vector4i[MaxGridSize.X * MaxGridSize.Y])
, Grid(MaxGridSize.X * MaxGridSize.Y)
, LightIndexLists(1)
, LightIndexListsTexture(LightIndexLists,Graphics::TextureFormat::R32i)
, PositionRange(1)
, ColorBuffer(1)
{
	Inputs["LightGrid"].Ref(Grid);
	Inputs["LightIndexLists"].Ref(LightIndexListsTexture);
	Inputs["LightPositionsRanges"].Ref(PositionRange);
	Inputs["LightColors"].Ref(ColorBuffer);
	Inputs["GridSize"].Ref(GridSize);
	Inputs["TileSize"].Ref(TileSize);
}

void LightGrid::Configure (const Camera &camera, const std::vector<Light*> &lights)
{
	std::vector<Math::Vector4i> screenspacelights;
	std::vector<unsigned int> lightindices;
	std::vector<Math::Vector4> posrange;
	std::vector<Math::Vector4> colors;

	//Find GridSize

	GridSize((camera.Width + TileSize - 1) / TileSize, (camera.Height + TileSize - 1) / TileSize);
	GridSize = std::min(GridSize, MaxGridSize);

	std::memset(CountsAndOffsetsCPU.get(), 0, sizeof(Math::Vector4i) * GridSize.X * GridSize.Y);


	//Find screenspace lights
	for (auto i = lights.begin (); i != lights.end(); ++i)
	{
		Math::Vector3 viewspace = camera.GetView() * (*i)->Transform.GetWorldPosition ();

		//(minx,miny,maxx,maxy)
		Math::Vector4 clipregion = ComputeClipRegion(viewspace, (*i)->Radius, camera.Near, camera.GetProjection());

		Math::Vector4i screenspace = ClipToScreenSpace (clipregion,camera);

		if (screenspace.X < screenspace.Z && screenspace.Y < screenspace.W)
		{
			screenspacelights.push_back(screenspace);

			DebugDraw::Line(Math::Vector3(), (*i)->Transform.GetWorldPosition());

			posrange.push_back(Math::Vector4(viewspace.X, viewspace.Y, viewspace.Z, (*i)->Radius));
			


			colors.push_back(Math::Vector4((*i)->Color.RedNorm() * (*i)->Intensity, (*i)->Color.GreenNorm() * (*i)->Intensity, (*i)->Color.BlueNorm() * (*i)->Intensity, 1.0));
		}
	}

	//Count each tile's

	int totallightentries = 0;

	for (auto i = screenspacelights.begin (); i != screenspacelights.end (); ++i)
	{
		Math::Vector2ui min ((*i).X,(*i).Y);
		Math::Vector2ui max ((*i).Z,(*i).W);

		min = Clamp (min / TileSize, Math::Vector2ui(0,0), Math::Vector2ui (GridSize.X + 1, GridSize.Y + 1));
		max = Clamp (Math::Vector2ui (max.X + TileSize - 1,max.Y + TileSize - 1) / TileSize, Math::Vector2ui(0,0), Math::Vector2ui (GridSize.X + 1, GridSize.Y + 1));

		for (unsigned int y = min.Y; y < max.Y; ++y)
		{
			for (unsigned int x = min.X; x < max.X; ++x)
			{
				CountsAndOffsets (x,y).X += 1;
				++totallightentries;
			}
		}
	}

	//CountsAndOffsets.X contains number of lights.


	unsigned int offset = 0;
	for (unsigned int y = 0; y < GridSize.Y; ++y)
	{
		for (unsigned int x = 0; x < GridSize.X; ++x)
		{
			unsigned count = CountsAndOffsets (x,y).X;
			CountsAndOffsets(x,y).Y = offset + count;
			offset += count;
		}
	}

	//CountsAndOffsets.Y contains index of end of light sublist

	//Allocate mores space if necessary
	if (LightIndexListsCPU.size () < totallightentries)
	{
		LightIndexListsCPU.resize(totallightentries);
	}

	//Insert light ID's
	for (auto i = screenspacelights.begin (); i != screenspacelights.end (); ++i)
	{
		Math::Vector2ui min ((*i).X,(*i).Y);
		Math::Vector2ui max ((*i).Z,(*i).W);

		min = Clamp(min / TileSize, Math::Vector2ui(0, 0), Math::Vector2ui(GridSize.X + 1, GridSize.Y + 1));
		max = Clamp(Math::Vector2ui(max.X + TileSize - 1, max.Y + TileSize - 1) / TileSize, Math::Vector2ui(0, 0), Math::Vector2ui(GridSize.X + 1, GridSize.Y + 1));

		for (unsigned int y = min.Y; y < max.Y; ++y)
		{
			for (unsigned int x = min.X; x < max.X; ++x)
			{
				unsigned int offset = CountsAndOffsets(x,y).Y - 1;
				LightIndexListsCPU[offset] = i - screenspacelights.begin();
				//std::cout << LightIndexListsCPU[offset] << std::endl;
				CountsAndOffsets(x,y).Y = offset;
			}
		}
	}


	//std::cout << "==Counts and Offsets==" << std::endl;
	//for (unsigned int y = 0; y < GridSize.Y; ++y)
	//{
	//	
	//	for (unsigned int x = 0; x < GridSize.X; ++x)
	//	{
	//		std::cout << "<" << CountsAndOffsets(x, y).X << ", " << CountsAndOffsets(x, y).Y << ">";
	//
	//		//CountsAndOffsets(x, y)(x, y,0,0);
	//	}
	//	std::cout << std::endl;
	//}

	//Copy to buffers
	Grid.Write(CountsAndOffsetsCPU.get(), GridSize.X * GridSize.Y);
	LightIndexLists.WriteCompletely(LightIndexListsCPU);

	//Write lights
	PositionRange.WriteCompletely(posrange);
	ColorBuffer.WriteCompletely(colors);
}



}}