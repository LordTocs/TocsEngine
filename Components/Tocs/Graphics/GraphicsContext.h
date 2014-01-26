#pragma once
#include "ContextTarget.h"
#include "IndexFormat.h"
#include <Tocs/Math/Color.h>
#include <string>

namespace Tocs {
namespace Graphics {

class GraphicsContext
{
	ContextTarget &Target;
	HGLRC hRC;

	unsigned int PixelFormat;
public:
	GraphicsContext(ContextTarget &target);
	~GraphicsContext();

	void *GetContext () const { return hRC; }
	ContextTarget &GetTarget () { return Target; }
	const ContextTarget &GetTarget () const { return Target; }

	void MakeCurrent ();
	bool HasExtension (std::string extension);

	void AlphaBlending ();
	void NormalBlending ();
	void AdditiveBlending ();

	void EnableDepthTest ();
	void DisableDepthTest ();
	void DisableDepthWrite ();
	void EnableDepthWrite ();

	void SetClearColor (Math::Color color);
	void SetClearDepth (float depth);
	void ClearActiveBuffer ();
	void ClearColor ();
	void ClearColor(Math::Color color);
	void ClearDepth ();

	void FlipToScreen ();

	void EnableWireframe ();
	void DisableWireframe ();

	void EnableBackfaceCulling ();
	void DisableBackfaceCulling ();

	void DrawTriangles (int triangles);
	void DrawTriangles (int offset, int length);
	void DrawTriangles (int offset, int length, const IndexFormat &format);

	void DrawTrianglesInstanced(int offset, int length, unsigned int instances, const IndexFormat &format);

	void DrawLines(int lines);

	void Compute(unsigned int groups);
	void Compute(unsigned int gwidth, unsigned int gheight);
	void Compute(unsigned int gwidth, unsigned int gheight, unsigned int gdepth);

	void AtomicCounterMemoryBarrier();

	void Viewport(unsigned int width, unsigned int height);

};

}}
