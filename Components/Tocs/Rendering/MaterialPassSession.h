#pragma once
#include <Tocs/Graphics/Shader.h>
#include <Tocs/Math/Transform.h>
#include "Camera.h"
namespace Tocs {
namespace Rendering {

class MaterialPassSession
{
	Graphics::Shader &BoundShader;
public:
	MaterialPassSession(Graphics::Shader &shader);
	~MaterialPassSession();

	Graphics::Shader &GetShader () { return BoundShader; }
	const Graphics::Shader &GetShader () const { return BoundShader; }

	void SetCamera (const Camera &cam);
	void SetTransform (const Math::Transform &transform);

};

}}