#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "ui/Viewport.h"
#include "ui/Toolbox.h"
#include "ui/dialogs.h"
#include "utils/objIO.h"

class MainWindow : public Gtk::Window {
	private:
		CG::Window _window;
		CG::DisplayFile _displayFile;
		Viewport _viewport;

		Toolbox _toolbox;
		Gtk::Box _mainBox;
		Glib::RefPtr<Gtk::ActionGroup> _actionGroup;
		Glib::RefPtr<Gtk::UIManager> _uiManager;

	public:
		MainWindow();
		void createPoint(std::string name, CG::Color color, CG::Coordinate c);
		void createLine(std::string name, CG::Color color, CG::Coordinate c1, CG::Coordinate c2);
		void createPolygon(std::string name, CG::Color color, CG::GObject::Coordinates coordinates);

	protected:
		void init_examples();
		void init_handlers();
		void init_leaf();
		void init_action_menu();

    // Event handlers
    void on_newPoint();
    void on_newLine();
    void on_newPolygon();
    void on_zoomIn()  { _viewport.changeWindowZoom(-1); }
    void on_zoomOut() { _viewport.changeWindowZoom(1); }
    void on_left()    { _viewport.changeWindowPosition(1,0);}
    void on_right()   { _viewport.changeWindowPosition(-1,0);}
    void on_up()      { _viewport.changeWindowPosition(0,-1);}
    void on_down()    { _viewport.changeWindowPosition(0,1);}
    void on_rotate_left()  { _viewport.rotateWindow(-15);}
    void on_rotate_right() { _viewport.rotateWindow(+15);}
		void on_action_file_open();
		void on_action_file_save();
};

#endif
