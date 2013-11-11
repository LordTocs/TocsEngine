#pragma once
#include <memory>
#include <Tocs/Math/Vector.h>
#include <Tocs/Rendering/Mesh.h>
#include "MeshBuilder.h"
#include <assert.h>

namespace Tocs {
namespace MeshTools {

class TileMask
{
public:
	char HasFace;

	TileMask()
		: HasFace (0)
	{}

	TileMask (bool face)
		: HasFace(face)
	{}

	bool Connectable (const TileMask &other)
	{
		return HasFace && other.HasFace;
	}
};

class GreedyTileMesher
{
	std::unique_ptr<TileMask[]> Mask;

	unsigned int Width;
	unsigned int Height;

	TileMask &GetMask (int x, int y) { return Mask[x + y * Width]; }
public:
	GreedyTileMesher(unsigned int width, unsigned int height)
		: Width(width),Height(height),
	      Mask (new TileMask[width * height] ())
	{}

	TileMask &operator()(unsigned int x, unsigned int y) { return Mask[x + y * Width]; }
	const TileMask &operator()(unsigned int x, unsigned int y) const { return Mask[x + y * Width]; }

	template <class V, class I>
	void Generate (const Math::Vector3 &origin, const Math::Vector3 &xaxis, const Math::Vector3 &yaxis, const Math::Vector3 &upaxis, MeshBuilder<V,I> &builder)
	{
		for (int y = 0; y < Height; ++y)
		{
			for (int x = 0; x < Width; ++x)
			{
				if (!GetMask(x,y).HasFace)
				{
					continue;
				}
				int quadwidth = 0;
				for (quadwidth = 1; GetMask(x,y).Connectable(GetMask(x + quadwidth,y)) && x + quadwidth < Width; ++quadwidth)
				{}

				int quadheight = 0;
				bool done = false;
				for(quadheight = 1; y + quadheight < Height; ++quadheight)
				{
					for (int k = 0; k < quadwidth; ++k)
					{
						if (!GetMask(x,y).Connectable(GetMask(x + k,y + quadheight)))
						{
							done = true;
							break;
						}
					}
					if (done)
						break;
				}

				auto v0 = builder.GetVertex();
				v0.Get().Position = origin + xaxis * x + yaxis * y;
				v0.Get().TextureCoordinate(0,0);
				auto v1 = builder.GetVertex();
				v1.Get().Position = origin + xaxis * (x + quadwidth) + yaxis * y;
				v1.Get().TextureCoordinate(quadwidth,0);
				auto v2 = builder.GetVertex();
				v2.Get().Position = origin + xaxis * x + yaxis * (y + quadheight);
				v2.Get().TextureCoordinate(0,quadheight);
				auto v3 = builder.GetVertex();
				v3.Get().Position = origin + xaxis * (x + quadwidth) + yaxis * (y + quadheight);
				v3.Get().TextureCoordinate(quadwidth,quadheight);
				auto quad = builder.CreateQuad(v2,v3,v1,v0);
				
				quad.first.FaceNormal(upaxis);
				quad.second.FaceNormal(upaxis);


				for (int i = 0; i < quadwidth; ++i)
				{
					for (int j = 0; j < quadheight; ++j)
					{
						GetMask(x + i,y + j).HasFace = false;
					}
				}
			}
		}
	}

};

}}
