#include "LayoutAble.h"
#include "ContainerBase.h"

namespace Tocs {
namespace Ui {

void LayoutAble::Parent(ContainerBase &container)
{
	if (Parent_ != nullptr)
	{
		Parent_->Remove(*this);
	}

	Parent_ = &container;
	
	container.InternalAdd(*this);
}

void LayoutAble::UnParent()
{
	if (Parent_ == nullptr)
		return;
	Parent_->InternalRemove(*this);
	Parent_ = nullptr;
}

}}