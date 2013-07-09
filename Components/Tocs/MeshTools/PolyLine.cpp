#include "PolyLine.h"

namespace Tocs {
namespace MeshTools {

void PolyLine::Add(const Math::Vector2 &point)
{
	Points.push_back(point);
	Bounds.Encapsulate(point);
}

}}