#pragma once

namespace Tocs {
namespace Math {

template <class T>
class ToReal
{
};

template <>
class ToReal<int>
{
public:
	typedef float Type;
};
template <>
class ToReal<unsigned int>
{
public:
	typedef float Type;
};
template <>
class ToReal<short>
{
public:
	typedef float Type;
};
template <>
class ToReal<unsigned short>
{
public:
	typedef float Type;
};
template <>
class ToReal<float>
{
public:
	typedef float Type;
};
template <>
class ToReal<double>
{
public:
	typedef double Type;
};

template <class T1, class T2>
class Promote
{
public:
	typedef decltype(T1() + T2()) Result;
};

}}