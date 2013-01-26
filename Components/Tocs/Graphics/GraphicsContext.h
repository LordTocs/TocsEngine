#pragma once
#include "ContextTarget.h"
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

	void EnableDepthBuffering ();
	void DisableDepthBuffering ();

	void SetClearColor (Math::Color color);
	void SetClearDepth (float depth);
	void ClearActiveBuffer ();

	void FlipToScreen ();

	static void DrawTriangles (int triangles);
	static void DrawTriangles (int offset, int length);

};

}}
