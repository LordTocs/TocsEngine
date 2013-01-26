#pragma once
#include <vector>
#include "Context.h"
#include "Event.h"

#include "BufferBase.h"


struct _cl_command_queue;

namespace Tocs {
namespace Parallel {

class IntermediateEvent;
class KernelBase;
class Image2D;
class Image3D;

class CommandQueue
{
	_cl_command_queue *QueuePtr;
	Context &_Context;
	CommandQueue(const CommandQueue &);
	CommandQueue &operator= (const CommandQueue &);
public:
	CommandQueue(Context &context);
	~CommandQueue(void);

	Context &GetContext () { return _Context; }
	const Context &GetContext () const { return _Context; }

	void Finish ();

	Event ExecKernel  (const KernelBase &kernel, unsigned int dimensions, unsigned int *sizes, unsigned int *offsets, unsigned int *localsizes, std::vector<Event> events);
	Event ReadBuffer  (const BufferBase &buffer, unsigned int offset, unsigned int length, void *dest, std::vector<Event> events);
	Event WriteBuffer (const BufferBase &buffer, unsigned int offset, unsigned int length, void *dest, std::vector<Event> events);
	Event WriteImage2D (const Image2D &img, unsigned int offsetx, unsigned int offsety, unsigned int width, unsigned int height, const void *data, std::vector<Event> events);
	Event ReadImage2D (const Image2D &img, unsigned int offsetx, unsigned int offsety, unsigned int width, unsigned int height, void *dest, std::vector<Event> events);
	Event WriteImage3D (const Image3D &img, unsigned int offsetx, unsigned int offsety, unsigned int offsetz,  unsigned int width, unsigned int height, unsigned int depth,  const void *data, std::vector<Event> events);
	Event ReadImage3D (const Image3D &img, unsigned int offsetx, unsigned int offsety, unsigned int offsetz, unsigned int width, unsigned int height, unsigned int depth, void *dest, std::vector<Event> events);

	Event Acquire (const Image3D &image, std::vector<Event> events);
	Event Acquire (const Image2D &image, std::vector<Event> events);
	Event Acquire (const BufferBase &buffer, std::vector<Event> events);

	Event Release (const Image3D &image, std::vector<Event> events);
	Event Release (const Image2D &image, std::vector<Event> events);
	Event Release (const BufferBase &buffer, std::vector<Event> events);

	CommandQueue &operator () (IntermediateEvent &evt);

	
};

}}