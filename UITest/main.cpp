#include <Tocs/Ui/App.h>
#include <Tocs/Ui/Window.h>
#include <Tocs/Ui/Button.h>
#include <Tocs/Ui/TextBox.h>
#include <Tocs/Ui/LayoutHelpers.h>
using namespace Tocs::Ui;

int main()
{
	Window w("Test Window", Size(200, 200));

	Button b1 ("Button 1");
	Button b2 ("Button 2");
	Button b3 ("Button 3");
	Button b4 ("Button 4");
	TextBox t1;




	b1.OnClick = [&](){ std::cout << "Button 1" << std::endl; b1.SetLabel("Clicked"); };
	b1.Area.Width.Strength(2);
	b2.OnClick = [&](){ std::cout << "Button 2" << std::endl; b2.SetLabel("Clicked"); };
	b3.OnClick = [&](){ std::cout << "Button 3" << std::endl; b3.SetLabel("Clicked"); };
	b4.OnClick = [&](){ std::cout << "Button 4" << std::endl; b4.SetLabel("Clicked"); };
	b4.Area.Width.Strength(2);
	b1.Area.BottomMargin = 0;
	b2.Area.BottomMargin = 0;
	b1.Area.RightMargin = 0;
	b3.Area.RightMargin = 0;

	w.Layout(w.Layout.Vertical({ w.Layout.Horizontal({ b1, b2 }),
							     w.Layout.Horizontal({ b3, b4 }),
								 t1
							   }));

	w.Show();

	App::PumpMessages();

	return 0;
}
