#include <Tocs/Ui/App.h>
#include <Tocs/Ui/Window.h>
#include <Tocs/Ui/Button.h>
#include <Tocs/Ui/TextBox.h>
#include <Tocs/Ui/ComboBox.h>
#include <Tocs/Ui/LayoutHelpers.h>
#include <cmath>
using namespace Tocs::Ui;



int main()
{


	Window w("Test Window", Size(400, 400));

	Button b1 ("Add");
	Button b2 ("Show");
	TextBox t1;
	ComboBox c1;




	b1.OnClick = [&]()
	{
		if (t1.Text().length() > 0)
		{
			c1.AddItem(t1.Text());
		}
	};
	b2.OnClick = [&]()
	{
		if (c1.HasSelection())
		{
			std::cout << c1.SelectedItem().Text() << std::endl;
		}
	};

	w.Layout(w.Layout.Vertical(
	{ 
		w.Layout.Horizontal({ b1, b2 }),
		w.Layout.Horizontal({ t1, c1 })
	}));

	w.Show();

	App::PumpMessages();

	return 0;
}
