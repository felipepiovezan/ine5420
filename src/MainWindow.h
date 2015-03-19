#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "Viewport.h"
#include "Toolbox.h"
#include "dialogs.h"

class MainWindow : public Gtk::Window {
	private:
		CG::Window _window;
		CG::DisplayFile _displayFile;
		Viewport _viewport;
		Toolbox _toolbox;
		Gtk::Box _mainBox;

	public:
		MainWindow();
		void createPoint(std::string name, CG::Color color, CG::Coordinate c);
		void createLine(std::string name, CG::Color color, CG::Coordinate c1, CG::Coordinate c2);
		void createPolygon(std::string name, CG::Color color, CG::GObject::Coordinates coordinates);

	protected:
		void init_examples();
		void init_handlers();
		void init_leaf();

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
