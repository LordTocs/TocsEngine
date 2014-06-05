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


	Window w("Test Window", Size(200, 200));

	Button b1 ("Button 1");
	TextBox t1;
	ComboBox c1;



	b1.OnClick = [&]()
	{ 
		std::cout << t1.Text() << std::endl;
	};
	b1.Area.Width.Strength(2);

	w.Layout(w.Layout.Vertical({ b1,
								 t1,
								 c1
							   }));

	w.Show();

	App::PumpMessages();

	return 0;
}
