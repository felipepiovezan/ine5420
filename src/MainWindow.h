#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "Viewport.h"
#include "Toolbox.h"
#include "dialogs.h"

class MainWindow : public Gtk::Window {
	private:
		Gtk::Box _mainBox;
		Viewport _viewport;
		Toolbox _toolbox;

	public:
		MainWindow();
		void createPoint(std::string name, CG::Coordinate c);
		void createLine(std::string name, CG::Coordinate c1, CG::Coordinate c2);
		void createPolygon(std::string name, CG::GObject::Coordinates coordinates);

	protected:
		void init_viewport();
		void init_handlers();

    // Event handlers
    void on_newPoint();
    void on_newLine();
    void on_newPolygon();
    void on_zoomIn() { _viewport.zoomIn(); }
    void on_zoomOut() { _viewport.zoomOut(); }
    void on_left() { _viewport.left(); }
    void on_right() { _viewport.right(); }
    void on_up() { _viewport.up(); }
    void on_down() { _viewport.down(); }
};

#endif
