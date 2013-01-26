#pragma once
#include "RenderSystem.h"
#include <Tocs/Math/Transform.h>

namespace Tocs {
namespace Rendering {

class RenderObject
{
	RenderSystem *System;
public:
	Math::Transform Transform;
	RenderSystem &GetSystem () { return *System;}
	bool HasSystem () const { return System != nullptr; }

	RenderObject()
		: System(nullptr) {}

	virtual ~RenderObject();

	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual void Update (float dt) = 0;
};


}}

