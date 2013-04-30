#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"
#include "Matrix4.h"
#include "Quaternion.h"

namespace Tocs {
namespace Math {

template <class T>
class IsMathType
{
public:
	static const bool Value = false;
};

template <>
class IsMathType<Vector3>
{
public:
	static const bool Value = true;
};

template <>
class IsMathType<Vector2>
{
public:
	static const bool Value = true;
};

template <>
class IsMathType<Color>
{
public:
	static const bool Value = true;
};

template <>
class IsMathType<Matrix4>
{
public:
	static const bool Value = true;
};

template <>
class IsMathType<Quaternion>
{
public:
	static const bool Value = true;
};

}}