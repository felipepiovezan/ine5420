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

	protected:
		void init_viewport();
		void init_handlers();

    // Event handlers
    void on_newPoint();
    void on_newLine();
    void on_newPolygon();
    void on_zoomIn();
    void on_zoomOut();
};

#endif
