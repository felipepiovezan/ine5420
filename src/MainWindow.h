#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "Viewport.h"
#include "Toolbox.h"

class MainWindow : public Gtk::Window {
	private:
		Gtk::Box _mainBox;
		Viewport _viewport;
		Toolbox _toolbox;

	public:
		MainWindow();

	private:
		//init functions
		void init_viewport();

		//signal handlers
		void on_Zoom_Changed();
};

#endif
