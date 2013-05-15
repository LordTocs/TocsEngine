#include "Transform.h"


namespace Tocs {
namespace Math {

Transform::Transform(void)
	: Scale (1,1,1)
{
	CreateMatrix ();
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