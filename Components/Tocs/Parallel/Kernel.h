#pragma once
#include "KernelBase.h"
#include "IntermediateEvent.h"
#include "KernelParamTypes.h"
#include <memory>
namespace Tocs {
namespace Parallel {

template <class>
class Kernel;

template <class A0>
class Kernel <void(A0)>
{
	KernelBase Base;
public:
	typedef typename KernelParamType<A0>::Type Arg0Type;
	//Template this with dimension?
	class ExecEvent : public IntermediateEvent
	{
		unsigned int Dimensions;
		unsigned int Sizes [3];
		unsigned int Offsets [3];
		unsigned int LocalSizes [3];
		bool UseLocalSize;
		Arg0Type Arg0;
		KernelBase &Base;

	public:
		ExecEvent(KernelBase &base, Arg0Type arg0)
			: Dimensions(0),
			  Base(base),
			  Arg0(std::move(arg0)),
			  Sizes(),
			  Offsets(),
			  LocalSizes(),
			  UseLocalSize(false)
		{
		}

		ExecEvent &Dim1(unsigned int size)
		{
			Dimensions=1;
			Sizes[0] = size;
			Sizes[1] = 0;
			Sizes[2] = 0;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &Dim2(unsigned int width, unsigned int height)
		{
			Dimensions=2;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = 0;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &Dim3(unsigned int width, unsigned int height, unsigned int length)
		{
			Dimensions=3;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = length;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &LocalDim1 (unsigned int localsize)
		{
			UseLocalSize = true;
			LocalSizes[0] = localsize;
			return *this;
		}

		ExecEvent &LocalDim2 (unsigned int localwidth, unsigned int localheight)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			return *this;
		}

		ExecEvent &LocalDim3 (unsigned int localwidth, unsigned int localheight, unsigned int localdepth)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			LocalSizes[2] = localdepth;
			return *this;
		}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			Base.SetArg (0,Arg0);
			ResultEvents.push_back(queue.ExecKernel(Base,Dimensions,&Sizes[0],&Offsets[0], (UseLocalSize ? &LocalSizes[0] : nullptr),dependants));
		}

	};

	Kernel (KernelBase base)
		: Base(base) {}

	ExecEvent operator () (Arg0Type arg0)
	{
		return ExecEvent (Base,arg0);
	}

	void SetBase (KernelBase &base) { Base = base; }
};

template <class A0, class A1>
class Kernel <void(A0, A1)>
{
	KernelBase Base;
public:
	typedef typename KernelParamType<A0>::Type Arg0Type;
	typedef typename KernelParamType<A1>::Type Arg1Type;
	//Template this with dimension?
	class ExecEvent : public IntermediateEvent
	{
		unsigned int Dimensions;
		unsigned int Sizes [3];
		unsigned int Offsets [3];
		unsigned int LocalSizes [3];
		bool UseLocalSize;
		Arg0Type Arg0;
		Arg1Type Arg1;
		KernelBase &Base;

	public:
		ExecEvent(KernelBase &base, Arg0Type arg0, Arg1Type arg1)
			: Dimensions(0),
			  Base(base),
			  Arg0(std::move(arg0)),
			  Arg1(std::move(arg1)),
			  Sizes(),
			  Offsets(),
			  UseLocalSize(false)
		{
		}

		ExecEvent &Dim1(unsigned int size)
		{
			Dimensions=1;
			Sizes[0] = size;
			Sizes[1] = 0;
			Sizes[2] = 0;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &Dim2(unsigned int width, unsigned int height)
		{
			Dimensions=2;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = 0;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &Dim3(unsigned int width, unsigned int height, unsigned int length)
		{
			Dimensions=3;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = length;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &LocalDim1 (unsigned int localsize)
		{
			UseLocalSize = true;
			LocalSizes[0] = localsize;
			return *this;
		}

		ExecEvent &LocalDim2 (unsigned int localwidth, unsigned int localheight)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			return *this;
		}

		ExecEvent &LocalDim3 (unsigned int localwidth, unsigned int localheight, unsigned int localdepth)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			LocalSizes[2] = localdepth;
			return *this;
		}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			Base.SetArg (0,Arg0);
			Base.SetArg (1,Arg1);
			ResultEvents.push_back(queue.ExecKernel(Base,Dimensions,&Sizes[0],&Offsets[0], (UseLocalSize ? &LocalSizes[0] : nullptr),dependants));
		}

	};

	Kernel (KernelBase base)
		: Base(base) {}

	ExecEvent operator () (Arg0Type arg0, Arg1Type arg1)
	{
		return ExecEvent (Base,arg0,arg1);
	}

	void SetBase (KernelBase &base) { Base = base; }
};

template <class A0, class A1, class A2>
class Kernel <void(A0, A1, A2)>
{
	KernelBase Base;
public:
	typedef typename KernelParamType<A0>::Type Arg0Type;
	typedef typename KernelParamType<A1>::Type Arg1Type;
	typedef typename KernelParamType<A2>::Type Arg2Type;
	//Template this with dimension?
	class ExecEvent : public IntermediateEvent
	{
		unsigned int Dimensions;
		unsigned int Sizes [3];
		unsigned int Offsets[3];
		unsigned int LocalSizes [3];
		bool UseLocalSize;
		Arg0Type Arg0;
		Arg1Type Arg1;
		Arg2Type Arg2;
		KernelBase &Base;

	public:
		ExecEvent(KernelBase &base, Arg0Type arg0, Arg1Type arg1, Arg2Type arg2)
			: Dimensions(0),
			  Base(base),
			  Arg0(std::move(arg0)),
			  Arg1(std::move(arg1)),
			  Arg2(std::move(arg2)),
			  Sizes(),
			  Offsets(),
			  UseLocalSize(false)
		{
		}

		ExecEvent &Dim1(unsigned int size)
		{
			Dimensions=1;
			Sizes[0] = size;
			Sizes[1] = 0;
			Sizes[2] = 0;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &Dim2(unsigned int width, unsigned int height)
		{
			Dimensions=2;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = 0;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &Dim3(unsigned int width, unsigned int height, unsigned int length)
		{
			Dimensions=3;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = length;
			Offsets[0] = 0;
			Offsets[1] = 0;
			Offsets[2] = 0;
			return *this;
		}

		ExecEvent &LocalDim1 (unsigned int localsize)
		{
			UseLocalSize = true;
			LocalSizes[0] = localsize;
			return *this;
		}

		ExecEvent &LocalDim2 (unsigned int localwidth, unsigned int localheight)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			return *this;
		}

		ExecEvent &LocalDim3 (unsigned int localwidth, unsigned int localheight, unsigned int localdepth)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			LocalSizes[2] = localdepth;
			return *this;
		}

	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			Base.SetArg (0,Arg0);
			Base.SetArg (1,Arg1);
			Base.SetArg (2,Arg2);
			ResultEvents.push_back(queue.ExecKernel(Base,Dimensions,&Sizes[0],&Offsets[0], (UseLocalSize ? &LocalSizes[0] : nullptr),dependants));
		}

	};

	Kernel (KernelBase base)
		: Base(base) {}

	ExecEvent operator () (Arg0Type arg0, Arg1Type arg1, Arg2Type arg2)
	{
		return ExecEvent (Base,arg0,arg1,arg2);
	}

	void SetBase (KernelBase &base) { Base = base; }
};

template <class A0, class A1, class A2, class A3>
class Kernel <void(A0, A1, A2, A3)>
{
	KernelBase Base;
public:
	typedef typename KernelParamType<A0>::Type Arg0Type;
	typedef typename KernelParamType<A1>::Type Arg1Type;
	typedef typename KernelParamType<A2>::Type Arg2Type;
	typedef typename KernelParamType<A3>::Type Arg3Type;
	//Template this with dimension?
	class ExecEvent : public IntermediateEvent
	{
		unsigned int Dimensions;
		unsigned int Sizes [3];
		unsigned int LocalSizes [3];
		unsigned int Offsets[3];
		bool UseLocalSize;
		Arg0Type Arg0;
		Arg1Type Arg1;
		Arg2Type Arg2;
		Arg3Type Arg3;
		KernelBase &Base;

	public:
		ExecEvent(KernelBase &base, Arg0Type arg0, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
			: Dimensions(0),
			  Base(base),
			  Arg0(std::move(arg0)),
			  Arg1(std::move(arg1)),
			  Arg2(std::move(arg2)),
			  Arg3(std::move(arg3)),
			  Sizes(),
			  Offsets(),
			  UseLocalSize(false)
		{
		}

		ExecEvent &Dim1(unsigned int size)
		{
			Dimensions=1;
			Sizes[0] = size;
			Sizes[1] = 0;
			Sizes[2] = 0;
			return *this;
		}

		ExecEvent &Dim2(unsigned int width, unsigned int height)
		{
			Dimensions=2;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = 0;
			return *this;
		}

		ExecEvent &Dim3(unsigned int width, unsigned int height, unsigned int length)
		{
			Dimensions=3;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = length;
			return *this;
		}

		ExecEvent &LocalDim1 (unsigned int localsize)
		{
			UseLocalSize = true;
			LocalSizes[0] = localsize;
			return *this;
		}

		ExecEvent &LocalDim2 (unsigned int localwidth, unsigned int localheight)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			return *this;
		}

		ExecEvent &LocalDim3 (unsigned int localwidth, unsigned int localheight, unsigned int localdepth)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			LocalSizes[2] = localdepth;
			return *this;
		}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			Base.SetArg (0,Arg0);
			Base.SetArg (1,Arg1);
			Base.SetArg (2,Arg2);
			Base.SetArg (3,Arg3);
			ResultEvents.push_back(queue.ExecKernel(Base,Dimensions,&Sizes[0],&Offsets[0], (UseLocalSize ? &LocalSizes[0] : nullptr),dependants));
		}

	};

	Kernel (KernelBase base)
		: Base(base) {}

	ExecEvent operator () (Arg0Type arg0, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
	{
		return ExecEvent (Base,arg0,arg1,arg2,arg3);
	}

	void SetBase (KernelBase &base) { Base = base; }
};

template <class A0, class A1, class A2, class A3, class A4>
class Kernel <void(A0, A1, A2, A3, A4)>
{
	KernelBase Base;
public:
	typedef typename KernelParamType<A0>::Type Arg0Type;
	typedef typename KernelParamType<A1>::Type Arg1Type;
	typedef typename KernelParamType<A2>::Type Arg2Type;
	typedef typename KernelParamType<A3>::Type Arg3Type;
	typedef typename KernelParamType<A4>::Type Arg4Type;
	//Template this with dimension?
	class ExecEvent : public IntermediateEvent
	{
		unsigned int Dimensions;
		unsigned int Sizes [3];
		unsigned int LocalSizes [3];
		unsigned int Offsets[3];
		bool UseLocalSize;
		Arg0Type Arg0;
		Arg1Type Arg1;
		Arg2Type Arg2;
		Arg3Type Arg3;
		Arg4Type Arg4;
		KernelBase &Base;

	public:
		ExecEvent(KernelBase &base, Arg0Type arg0, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
			: Dimensions(0),
			  Base(base),
			  Arg0(std::move(arg0)),
			  Arg1(std::move(arg1)),
			  Arg2(std::move(arg2)),
			  Arg3(std::move(arg3)),
			  Arg4(std::move(arg4)),
			  Sizes(),
			  Offsets(),
			  UseLocalSize(false)
		{
		}

		ExecEvent &Dim1(unsigned int size)
		{
			Dimensions=1;
			Sizes[0] = size;
			Sizes[1] = 0;
			Sizes[2] = 0;
			return *this;
		}

		ExecEvent &Dim2(unsigned int width, unsigned int height)
		{
			Dimensions=2;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = 0;
			return *this;
		}

		ExecEvent &Dim3(unsigned int width, unsigned int height, unsigned int length)
		{
			Dimensions=3;
			Sizes[0] = width;
			Sizes[1] = height;
			Sizes[2] = length;
			return *this;
		}

		ExecEvent &LocalDim1 (unsigned int localsize)
		{
			UseLocalSize = true;
			LocalSizes[0] = localsize;
			return *this;
		}

		ExecEvent &LocalDim2 (unsigned int localwidth, unsigned int localheight)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			return *this;
		}

		ExecEvent &LocalDim3 (unsigned int localwidth, unsigned int localheight, unsigned int localdepth)
		{
			UseLocalSize = true;
			LocalSizes[0] = localwidth;
			LocalSizes[1] = localheight;
			LocalSizes[2] = localdepth;
			return *this;
		}
	protected:
		void Enqueue (CommandQueue &queue)
		{
			std::vector<Event> dependants = (Dependant != nullptr ? Dependant->GetResultEvents(queue) : std::vector<Event> ());
			Base.SetArg (0,Arg0);
			Base.SetArg (1,Arg1);
			Base.SetArg (2,Arg2);
			Base.SetArg (3,Arg3);
			Base.SetArg (4,Arg4);
			ResultEvents.push_back(queue.ExecKernel(Base,Dimensions,&Sizes[0],&Offsets[0], (UseLocalSize ? &LocalSizes[0] : nullptr),dependants));
		}

	};

	Kernel (KernelBase base)
		: Base(base) {}

	ExecEvent operator () (Arg0Type arg0, Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4)
	{
		return ExecEvent (Base,arg0,arg1,arg2,arg3,arg4);
	}

	void SetBase (KernelBase &base) { Base = base; }
};
}}