#include "LayoutManager.h"
#include "ContainerBase.h"
#include "LayoutHelpers.h"
#include "LayoutContainer.h"

namespace Tocs {
namespace Ui {

	void LayoutManager::Layout(Point p, Size s)
	{
		if (Root != nullptr)
			Root->LayoutContents(p, s);
	}

	LayoutManager::LayoutManager(LayoutContainer *owner)
		: Owner(owner), Root(nullptr)
	{

	}

	LayoutHelper &LayoutManager::Vertical(std::initializer_list<LayoutRef> elements)
	{
		VerticalLayoutHelper *helper = new VerticalLayoutHelper();

		for (auto l : elements)
		{
			helper->Add(l.Get());
		}

		IntermediateContainers.emplace_back(helper);

		return *helper;
	}
	LayoutHelper &LayoutManager::Horizontal(std::initializer_list<LayoutRef> elements)
	{
		HorizontalLayoutHelper *helper = new HorizontalLayoutHelper();

		for (auto l : elements)
		{
			helper->Add(l.Get());
		}

		IntermediateContainers.emplace_back(helper);

		return *helper;
	}

	LayoutManager &LayoutManager::operator()(LayoutHelper &helper)
	{
		Root = &helper;
		Owner->Add(helper);
		return *this;
	}


}}