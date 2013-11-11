#include "Transform.h"


namespace Tocs {
namespace Math {

Transform::Transform()
	: Scale (1,1,1)
{
	CreateMatrix ();
}

Transform::Transform(Vector3 pos)
: Scale(1, 1, 1), Position(pos)
{
	CreateMatrix();
}

void Transform::CreateMatrix ()
{
	TransformMatrix = Matrix4::CreateTranslation (Position) *  Matrix4::CreateRotation (Rotation) * Matrix4::CreateScale (Scale) ;
}

Vector3 Transform::GetWorldPosition ()
{
	return Position;
}


}}