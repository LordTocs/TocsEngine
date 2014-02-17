#include "LayoutContainer.h"

namespace Tocs {
namespace Ui {
	//hhhnjhj

void LayoutContainer::DoLayout(Point p, Size s)
{
	Layout.Layout(p, s);
}

Size LayoutContainer::GetMinimumSize() const
{
	if (Layout.Root != nullptr)
		return Layout.Root->GetMinimumSize();

	return Size(0, 0);
	
}


}}
