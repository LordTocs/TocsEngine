#include "CommandQueue.h"
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include "IntermediateEvent.h"
#include "KernelBase.h"
#include "Image2D.h"
#include "Image3D.h"
#include <iostream>
#include "ErrorCheck.h"

using namespace std;

namespace Tocs {
namespace Parallel {

CommandQueue::CommandQueue(Context &context)
	: QueuePtr(nullptr),
	  _Context(context)
{
	int error;
	QueuePtr = clCreateCommandQueue (context.GetCLPtr(),context.GetDevice().GetCLPtr(),0,&error);
}


CommandQueue::~CommandQueue(void)
{
	clReleaseCommandQueue (QueuePtr);
}

void CommandQueue::Finish ()
{
	clFinish (QueuePtr);
}

//////////////////////////////////////


Event CommandQueue::ExecKernel (const KernelBase &kernel, unsigned int dimensions, unsigned int *sizes, unsigned int *offset, unsigned int *localsizes, std::vector<Event> depends)
{
	//cout << "Queueing Kernel in " << dimensions << " depending on " << depends.size () <<endl;
	cl_event evt;

	int error = clEnqueueNDRangeKernel (QueuePtr,kernel.GetCLPtr (),dimensions,nullptr,sizes,localsizes,depends.size(),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)), &evt);
	if (CheckError(error))
	{
		cout << "Error Executing Kernel: " << endl
			<< kernel.GetName () << "<";

		for (int i = 0; i < dimensions; ++i)
		{
			cout << sizes[i];
			if (i != dimensions-1)
				cout << ", ";
		}
		 cout << ">" << endl;
	}
	//cout << "\terr: " << error << endl;
	Event result (evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::ReadBuffer  (const BufferBase &buffer, unsigned int offset, unsigned int length, void *dest, std::vector<Event> depends)
{
	//cout << "Queueing Read:" << length << " depending on " << depends.size () <<endl;
	//cout << "\tOffset: " << offset << " Length: " << length << endl;
	cl_event evt;
	int error = clEnqueueReadBuffer(QueuePtr,buffer.GetCLPtr (),false,offset,length,dest,depends.size(),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Error Reading" << endl;
	}
	//cout << "\terr: " << error << endl;
	Event result (evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::WriteBuffer (const BufferBase &buffer, unsigned int offset, unsigned int length, void *data, std::vector<Event> depends)
{
	//cout << "Queueing Write: " << length << " depending on " << depends.size () << endl;
	//cout << "\tOffset: " << offset << " Length: " << length << endl;
	cl_event evt;
	int error = clEnqueueWriteBuffer(QueuePtr,buffer.GetCLPtr (),false,offset,length,data,depends.size(),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Error Writing" << endl;
	}
	//cout << "\terr: " << error << endl;
	Event result (evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::WriteImage2D (const Image2D &img, unsigned int offsetx, unsigned int offsety, unsigned int width, unsigned int height, const void *data, std::vector<Event> depends)
{
	//cout << "Queueing Write 2D depending on " << depends.size () << endl;
	unsigned int offset [3] = {offsetx, offsety, 0};
	unsigned int size [3] = {width, height, 1};
	cl_event evt = nullptr;
	int error = clEnqueueWriteImage (QueuePtr,img.GetCLPtr (),false,offset,size,width*img.GetFormat().PixelSizeInBytes(),0,data,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Error Writing 2D" << endl;
	}

	Event result(evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::ReadImage2D (const Image2D &img, unsigned int offsetx, unsigned int offsety, unsigned int width, unsigned int height, void *dest, std::vector<Event> depends)
{
	//cout << "Queueing Read 2D: " << endl;
	unsigned int offset [3] = {offsetx, offsety, 0};
	unsigned int size [3] = {width, height, 1};
	cl_event evt;
	int error = clEnqueueReadImage (QueuePtr,img.GetCLPtr (),false,offset,size,width*img.GetFormat().PixelSizeInBytes(),0,dest,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Error Writing 2D" << endl;
	}

	Event result(evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::WriteImage3D (const Image3D &img, unsigned int offsetx, unsigned int offsety, unsigned int offsetz,  unsigned int width, unsigned int height, unsigned int depth,  const void *data, std::vector<Event> depends)
{
	//cout << "Queueing Write 3D depending on " << depends.size () << endl;
	unsigned int offset [3] = {offsetx, offsety, offsetz};
	unsigned int size [3] = {width, height, depth};
	cl_event evt = nullptr;
	int error = clEnqueueWriteImage (QueuePtr,img.GetCLPtr (),false,offset,size,width*img.GetFormat().PixelSizeInBytes(),0,data,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Error Writing 3D" << endl;
	}

	Event result(evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::ReadImage3D (const Image3D &img, unsigned int offsetx, unsigned int offsety, unsigned int offsetz, unsigned int width, unsigned int height, unsigned int depth, void *dest, std::vector<Event> depends)
{
	//cout << "Queueing Read 3D: " << endl;
	unsigned int offset [3] = {offsetx, offsety, offsetz};
	unsigned int size [3] = {width, height, depth};
	cl_event evt;
	int error = clEnqueueReadImage (QueuePtr,img.GetCLPtr (),false,offset,size,width*img.GetFormat().PixelSizeInBytes(),0,dest,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Error Reading 3D" << endl;
	}

	Event result(evt);
	clReleaseEvent (evt);
	return result;
}

Event CommandQueue::Acquire (const Image3D &image, std::vector<Event> depends)
{
	cl_event evt;
	const cl_mem buffer [1] = {image.GetCLPtr ()};
	int error = clEnqueueAcquireGLObjects (QueuePtr,1,buffer,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Acquiring Image3D" << endl;
	}
	Event result(evt);
	clReleaseEvent(evt);
	return result;
}
Event CommandQueue::Acquire (const Image2D &image, std::vector<Event> depends)
{
	cl_event evt;
	const cl_mem buffer [1] = {image.GetCLPtr ()};
	int error = clEnqueueAcquireGLObjects (QueuePtr,1,buffer,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Acquiring Image2D" << endl;
	}
	Event result(evt);
	clReleaseEvent(evt);
	return result;
}
Event CommandQueue::Acquire (const BufferBase &buffer, std::vector<Event> depends)
{
	cl_event evt;
	const cl_mem bufferarr [1] = {buffer.GetCLPtr ()};
	int error = clEnqueueAcquireGLObjects (QueuePtr,1,bufferarr,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Acquiring Buffer" << endl;
	}
	Event result(evt);
	clReleaseEvent(evt);
	return result;
}

Event CommandQueue::Release (const Image3D &image, std::vector<Event> depends)
{
	cl_event evt;
	const cl_mem bufferarr [1] = {image.GetCLPtr ()};
	int error = clEnqueueReleaseGLObjects (QueuePtr,1,bufferarr,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Releasing Image3D" << endl;
	}
	Event result(evt);
	clReleaseEvent(evt);
	return result;
}
Event CommandQueue::Release (const Image2D &image, std::vector<Event> depends)
{
	cl_event evt;
	const cl_mem bufferarr [1] = {image.GetCLPtr ()};
	int error = clEnqueueReleaseGLObjects (QueuePtr,1,bufferarr,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Releasing Image2D" << endl;
	}
	Event result(evt);
	clReleaseEvent(evt);
	return result;
}
Event CommandQueue::Release (const BufferBase &buffer, std::vector<Event> depends)
{
	cl_event evt;
	const cl_mem bufferarr [1] = {buffer.GetCLPtr ()};
	int error = clEnqueueReleaseGLObjects (QueuePtr,1,bufferarr,depends.size (),reinterpret_cast<cl_event *>((depends.size() != 0 ? &depends[0] : nullptr)),&evt);
	if (CheckError(error))
	{
		cout << "##Releasing Buffer" << endl;
	}
	Event result(evt);
	clReleaseEvent(evt);
	return result;
}

CommandQueue &CommandQueue::operator () (IntermediateEvent &evt)
{
	evt.GetResultEvents (*this);
	return *this;
}

}}