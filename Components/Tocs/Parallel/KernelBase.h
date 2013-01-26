#pragma once
#include <string>
#include "Buffer.h"
#include "Image2D.h"
#include "Image3D.h"
#include <iostream>
#include <typeinfo>

struct _cl_kernel;

namespace Tocs {
namespace Parallel {

class Program;

class KernelBase
{
	_cl_kernel *KernelPtr;
	void SetArgInternal (int arg, unsigned int size, const void *value);
public:
	KernelBase() : KernelPtr(nullptr) {}
	KernelBase(const KernelBase &copyme);
	KernelBase(Program &program, const std::string &name);
	~KernelBase();

	KernelBase &operator= (const KernelBase &copyme);

	_cl_kernel *GetCLPtr () const { return KernelPtr; }

	template <class T>
	void SetArg (int arg, const T &value)
	{
		SetArgInternal (arg,sizeof(T),&value);
		//std::cout << "SetArg: " << arg << " t:" << typeid(T).name () << " " << value << std::endl;
	}

	template <class T>
	void SetArg (int arg, const Buffer<T> &value)
	{
		auto ptr = value.GetCLPtr ();
		SetArgInternal (arg,sizeof (ptr),&ptr);
		//std::cout << "SetArgBuffer: " << arg << " t:" << typeid(T).name () << std::endl;
	}

	void SetArg (int arg, const Image2D &image)
	{
		auto ptr = image.GetCLPtr ();
		SetArgInternal (arg,sizeof (ptr),&ptr);
		//std::cout << "SetArgImage: " << arg << std::endl;
	}

	void SetArg (int arg, const Image3D &image)
	{
		auto ptr = image.GetCLPtr ();
		SetArgInternal (arg,sizeof (ptr),&ptr);
		//std::cout << "SetArgImage: " << arg << std::endl;
	}
	std::string GetName () const;
};



}}