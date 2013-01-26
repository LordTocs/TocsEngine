#pragma once
#include "Component.h"

namespace Tocs {
namespace Componentry {

class ExampleComponent : public Component<ExampleComponent>
{
public:
	Callback <int (std::string)> OnDerp;
	Attribute <float> SomeValue;
	ExampleComponent(Entity *owner)
		: Component<ExampleComponent> (owner)
	{
	}

	void ExposedFoo (int a)
	{
		a = OnDerp ("hello");
	}


	static std::string InitType ()
	{
		MetaData.Add (GenMetaData<ExampleComponent>::Method<void(int)>::Get<&ExposedFoo> ("ExposedFoo"));
		MetaData.Add (GenMetaData<ExampleComponent>::Callback<int(std::string)>::Get<&ExampleComponent::OnDerp> ("OnDerp"));
		MetaData.Add (GenMetaData<ExampleComponent>::Attribute<float>::Get<&ExampleComponent::SomeValue> ("SomeValue"));
		return "ExampleComponent";
	}
};


}}
