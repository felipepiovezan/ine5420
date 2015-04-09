#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include "utils/objIO.h"
#include "ui/Toolbox.h"
#include "ui/dialogs.h"
#include "ui/GtkUIViewport.h"
#include <iostream>
#include "cg/World.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include <memory>

class MainWindow : public Gtk::Window {
	private:
		std::shared_ptr<CG::World> _world;
		CG::Window _window;
		GtkUIViewport _viewport;

		Toolbox _toolbox;
		Gtk::Box _mainBox;
		Glib::RefPtr<Gtk::ActionGroup> _actionGroup;
		Glib::RefPtr<Gtk::UIManager> _uiManager;

	public:
		MainWindow();

	protected:
		void init_examples();
		void init_handlers();
		void init_leaf();
		void init_action_menu();

    // Event handlers
    void on_newPoint();
    void on_newLine();
    void on_newPolygon();
    void on_newCurve();
		void on_action_file_open();
		void on_action_file_save();

		// Keyboard handlers
		bool on_key_press_event(GdkEventKey* event);

    // Mouse handlers
    bool on_scroll_event(GdkEventScroll* event);
};

#endif
