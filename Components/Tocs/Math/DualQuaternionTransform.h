#pragma once
#include "Dual.h"
#include "Quaternion.h"
namespace Tocs {
namespace Math {

class DualQuaternionTransform
{
public:
	DualQuaternionTransform() = delete;

	template <class Kernel>
	static Math::Dual<QuaternionBase<Kernel>> ToDualQuaternion(const VectorBase<Kernel, 3> &translation, const QuaternionBase<Kernel> &rotation)
	{
		QuaternionBase<Kernel> t(translation.X * 0.5f, translation.Y * 0.5f, translation.Z * 0.5f, 0);

		return Math::Dual<QuaternionBase<Kernel>>(rotation, t * rotation);
	}

	template <class Kernel>
	static Math::VectorBase<Kernel, 3> ExtractPosition(const Math::Dual<QuaternionBase<Kernel>> &transform)
	{
		Quaternion pos = 2.0f * transform.DualPart * transform.RealPart.Conjugate();
		return Math::VectorBase<Kernel, 3>(pos.X, pos.Y, pos.Z);
	}

	template <class Kernel>
	static Math::VectorBase<Kernel, 3> TransformPoint(const VectorBase<Kernel, 3> &point, const Math::Dual<QuaternionBase<Kernel>> &transform)
	{

	}
};

}
}