#pragma once

namespace Tocs {
namespace Rendering {

class Primitives
{
	Primitives();
	Primitives(const Primitives &);
	static void LoadCube ();
public:
	static void LoadPrimitives ();
};

}}