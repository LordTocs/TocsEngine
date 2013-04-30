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
	TransformMatrix = Matrix4::CreateScale (Scale) * Matrix4::CreateRotation (Rotation) * Matrix4::CreateTranslation (Position);
}

Vector3 Transform::GetWorldPosition ()
{
	return Position;
}


}}