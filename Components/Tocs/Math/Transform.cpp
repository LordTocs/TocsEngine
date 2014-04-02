#include "Transform.h"


namespace Tocs {
namespace Math {

Transform::Transform()
: Scale_(1, 1, 1)
, Parent_(nullptr)
, TreeLevel(0)
, TreeLevelDirtyFlag(true)
, LocalTransformMatrixDirtyFlag(true)
, TransformDirtyFlag(true)
{
	CreateMatrix ();
	TransformArbitor::Global.Get().Add(this);
}

Transform::Transform(Vector3 pos)
: Scale_(1, 1, 1)
, Position_(pos)
, Parent_(nullptr)
, TreeLevel(0)
, TreeLevelDirtyFlag(true)
, LocalTransformMatrixDirtyFlag(true)
, TransformDirtyFlag(true)
{
	TransformArbitor::Global.Get().Add(this);
}

Transform::Transform(const Transform &copyme)
: Position_(copyme.Position_)
, Scale_(copyme.Scale_)
, Rotation_(copyme.Rotation_)
, Parent_(copyme.Parent_)
, TreeLevel(copyme.TreeLevel)
, TreeLevelDirtyFlag(copyme.TreeLevelDirtyFlag)
, LocalTransformMatrix(copyme.LocalTransformMatrix)
, LocalTransformMatrixDirtyFlag(copyme.LocalTransformMatrixDirtyFlag)
, TransformMatrix(copyme.TransformMatrix)
, TransformDirtyFlag(copyme.TransformDirtyFlag)
{
	TransformArbitor::Global.Get().Add(this);
}
Transform::~Transform()
{
	TransformArbitor::Global.Get().Remove(this);
}

void Transform::CreateMatrix ()
{
	if (LocalTransformMatrixDirtyFlag)
	{
		LocalTransformMatrix = Matrix4::CreateTranslation(Position_) *  Matrix4::CreateRotation(Rotation_) * Matrix4::CreateScale(Scale_);
		LocalTransformMatrixDirtyFlag = false;
		TransformDirtyFlag = true;
	}

	if (TransformDirtyFlag)
	{
		if (Parent_ == nullptr)
		{
			TransformMatrix = LocalTransformMatrix;
		}
		else
		{
			TransformMatrix = Parent_->GetMatrix() * LocalTransformMatrix;
		}
		TransformDirtyFlag = false;
	}
}

Vector3 Transform::GetWorldPosition ()
{
	return TransformMatrix * Vector3(0,0,0);
}

unsigned int Transform::Level()
{
	if (TreeLevelDirtyFlag)
	{
		if (Parent_ == nullptr)
		{
			TreeLevel = 0;
		}
		else
		{
			TreeLevel = 1 + Parent_->Level();
		}
		TreeLevelDirtyFlag = false;
	}
	return TreeLevel;
}

Transform &Transform::Parent(Transform &newparent)
{
	Parent_ = &newparent;
	TreeLevelDirtyFlag = true;
	TransformDirtyFlag = true;
	return *this;
}

void Transform::UnParent()
{
	Parent_ = nullptr;
	TreeLevelDirtyFlag = true;
	TransformDirtyFlag = true;
}

FirstUseStatic<TransformArbitor, TransformArbitor::GlobalArbitorConstructor> TransformArbitor::Global;

void TransformArbitor::Add(Transform *transform)
{
	Transforms.push_back(transform);
}
void TransformArbitor::Remove(Transform *transform)
{
	auto i = std::find(Transforms.begin(), Transforms.end(), transform);
	if (i != Transforms.end())
	{
		Transforms.erase(i);
	}
}
void TransformArbitor::ComputeTransformationMatricies()
{
	//Sort by tree level
	std::sort(Transforms.begin(), Transforms.end(), [](Transform *a, Transform*b) ->bool{return a->Level() < b->Level(); });

	//Assign global transform dirty flags

	for (auto i : Transforms)
	{
		if (i->Parent_ == nullptr)
			continue;
		i->TransformDirtyFlag = i->Parent_->TransformDirtyFlag || i->Parent_->LocalTransformMatrixDirtyFlag;
	}

	for (auto i : Transforms)
	{
		i->CreateMatrix();
	}
}



}}