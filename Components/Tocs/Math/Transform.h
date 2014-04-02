#pragma once
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include <Tocs/Core/LateStatic.h>
#include <vector>

namespace Tocs {
namespace Math {

class Transform
{
	Matrix4 TransformMatrix;
	bool TransformDirtyFlag;

	Matrix4 LocalTransformMatrix;
	bool LocalTransformMatrixDirtyFlag;

	Transform *Parent_;

	unsigned int TreeLevel;
	bool TreeLevelDirtyFlag;

	Vector3 Position_;
	Quaternion Rotation_;
	Vector3 Scale_;
public:
	friend class TransformArbitor;

	Transform();
	explicit Transform(Vector3 position);
	Transform(const Transform &copyme);
	~Transform();


	const Matrix4 &GetMatrix () const { return TransformMatrix; }

	void CreateMatrix ();

	Transform *Parent() { return Parent_; }
	const Transform *Parent() const { return Parent_; }
	Transform &Parent(Transform &newparent);
	
	void UnParent();

	unsigned int Level();
	
	Vector3 &Position() { LocalTransformMatrixDirtyFlag = true; return Position_; }
	const Vector3 &Position() const { return Position_; }

	Quaternion &Rotation() { LocalTransformMatrixDirtyFlag = true; return Rotation_; }
	const Quaternion &Rotation() const { return Rotation_; }

	Vector3 &Scale() { LocalTransformMatrixDirtyFlag = true; return Scale_; }
	const Vector3 &Scale() const { return Scale_; }

	Vector3 GetWorldPosition ();
};

class TransformArbitor
{
	std::vector<Transform*> Transforms;
	
public:
	static TransformArbitor GlobalArbitorConstructor() { return TransformArbitor(); }
	static FirstUseStatic<TransformArbitor, GlobalArbitorConstructor> Global;
	void Add(Transform *transform);
	void Remove(Transform *transform);

	void ComputeTransformationMatricies();

};

}}