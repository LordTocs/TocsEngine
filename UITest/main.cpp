#include <Tocs/Ui/App.h>
#include <Tocs/Ui/Window.h>
#include <Tocs/Ui/Button.h>

using namespace Tocs::Ui;

int main()
{
	Window w("Test Window", Size(200, 200));

	Button b("Test Button");
	b.Area.Margin(3);
	b.Area.Height.Max(50);
	b.Area.Width.Pixels(80);
	Button b2("Test Button2");
	b2.Area.Margin(3);
	b2.Area.Height.Max(50);
	b2.Area.Width.Strength(2.0);
	Button b3("Button 3");
	b3.Area.Margin(3);
	b3.Area.Width.Min(100);
	b3.Area.Height.Max(50);


	b.OnClick = [&](){ std::cout << "Button 1" << std::endl; b.SetLabel("Clicked"); };
	b2.OnClick = [&](){ std::cout << "Button 2" << std::endl; b2.SetLabel("Clicked"); w.Add(b3); };

	w.Add(b);
	w.Add(b2);

	w.Show();

	App::PumpMessages();

	return 0;
}
