#pragma once

#include <Tocs/Graphics/Texture.h>
#include <Tocs/Graphics/RenderTarget.h>
namespace Tocs {
namespace Rendering {

class RenderSystem;

class PostProcess
{
	bool Enabled_;
protected:
	RenderSystem *System;
	
public:
	PostProcess(RenderSystem &system)
		: System(&system), Enabled_(true) {}

	PostProcess(const PostProcess &) = delete;
	PostProcess &operator= (const PostProcess &) = delete;

	virtual ~PostProcess() {}

	virtual void Apply(const Graphics::Texture2D &sourcetexture, Graphics::RenderTarget &target) = 0;

	bool Enabled() { return Enabled_; }
	void Enabled(bool enabled) { Enabled_ = enabled; }
};

}}