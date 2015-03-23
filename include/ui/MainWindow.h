#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "ui/Viewport.h"
#include "ui/Toolbox.h"
#include "ui/dialogs.h"

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
    void on_zoomIn()  { _window.zoom(1.0); _viewport.redraw(); }
    void on_zoomOut() { _window.zoom(-1.0); _viewport.redraw(); }
    void on_left()    { _window.moveCenter(-1,0); _viewport.redraw(); }
    void on_right()   { _window.moveCenter(1,0); _viewport.redraw(); }
    void on_up()      { _window.moveCenter(0,1); _viewport.redraw(); }
    void on_down()    { _window.moveCenter(0,-1); _viewport.redraw(); }
    void on_rotate_left()  {} // TODO
    void on_rotate_right() {} // TODO 
};

#endif
