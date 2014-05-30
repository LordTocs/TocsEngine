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
		Math::Dual<QuaternionBase<Kernel>> t(QuaternionBase<Kernel>::Identity,QuaternionBase<Kernel>::PureQuaternion(translation * 0.5f));
		Math::Dual<QuaternionBase<Kernel>> r(rotation, QuaternionBase<Kernel>());
		return t * r;
	}

	template <class Kernel>
	static Math::VectorBase<Kernel, 3> ExtractPosition(const Math::Dual<QuaternionBase<Kernel>> &transform)
	{
		QuaternionBase<Kernel> pos = 2.0f * transform.DualPart * transform.RealPart.Conjugate();
		return Math::VectorBase<Kernel, 3>(pos.X, pos.Y, pos.Z);
	}

	template <class Kernel>
	static Math::VectorBase<Kernel, 3> TransformPoint(const VectorBase<Kernel, 3> &point, const Math::Dual<QuaternionBase<Kernel>> &transform)
	{
		Dual<QuaternionBase<Kernel>> pos (QuaternionBase<Kernel>::Identity, QuaternionBase<Kernel>(point.X, point.Y, point.Z, 0));
		Dual<QuaternionBase<Kernel>> conjconj (transform.RealPart.Conjugate(), transform.DualPart.Conjugate());
		conjconj = conjconj.Conjugate();
		pos = transform * pos * conjconj;
		return VectorBase<Kernel, 3>(pos.DualPart.X, pos.DualPart.Y, pos.DualPart.Z);
	}

	template <class Kernel>
	static Dual<QuaternionBase<Kernel>> Conjugate(const Dual<QuaternionBase<Kernel>> dq)
	{
		return Dual<QuaternionBase<Kernel>>(dq.RealPart.Conjugate(), dq.DualPart.Conjugate());
	}
};

}
}