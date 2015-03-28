#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "cg/World.h"
#include "utils/objIO.h"
#include "ui/Toolbox.h"
#include "ui/dialogs.h"
#include "ui/GtkUIViewport.h"
#include <iostream>

class MainWindow : public Gtk::Window {
	private:
		CG::World _world;
		CG::Window _window;
		GtkUIViewport _viewport;

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
		void on_action_file_open();
		void on_action_file_save();
};

#endif
