#pragma once
#include "Device.h"

struct _cl_context;

namespace Tocs {

namespace Graphics { class GraphicsContext; }

namespace Parallel {

class Context
{
	_cl_context *ContextPtr;
	Device &_Device;
public:
	Context(Device &device);
	Context(Device &device, Graphics::GraphicsContext &);

	~Context();

	Device &GetDevice () { return _Device; }
	const Device &GetDevice () const { return _Device; }

	_cl_context *GetCLPtr () { return ContextPtr; }
};

}}