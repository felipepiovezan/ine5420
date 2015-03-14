#include <gtkmm.h>
#include "Viewport.h"

class MainWindow : public Gtk::Window {
	public:
		MainWindow();

		Viewport viewport;
};
