#pragma once
#include <Tocs/Core/Asset.h>
#include "Mesh.h"
#include "Drawable.h"

namespace Tocs {
namespace Rendering {

class StaticMesh : public Drawable
{
public:
	StaticMesh(RenderSystem &system, const Asset<Mesh> mesh);


};

}}
