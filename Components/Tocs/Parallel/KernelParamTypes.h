#pragma once
#include "Buffer.h"
#include "Image2D.h"
#include "Image3D.h"

namespace Tocs {
namespace Parallel {

template <class T>
class KernelParamType
{
	KernelParamType();
	KernelParamType(const KernelParamType &);
public:
	typedef T Type;
};

template <class T>
class KernelParamType <T*>
{
	KernelParamType();
	KernelParamType(const KernelParamType &);
public:
	typedef Buffer<T> & Type;
};

template <>
class KernelParamType<Image2D>
{
	KernelParamType();
	KernelParamType(const KernelParamType &);
public:
	typedef Image2D &Type;
};


template <>
class KernelParamType<Image3D>
{
	KernelParamType();
	KernelParamType(const KernelParamType &);
public:
	typedef Image3D &Type;
};
}}