#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "Viewport.h"

class MainWindow : public Gtk::Window {
	private:
		Viewport _viewport;
	
	public:
		MainWindow();

	private:
		//init functions
		void init_buttons_and_sliders();
		void init_viewport();

		//signal handlers
		void on_Zoom_Changed();
};

#endif
