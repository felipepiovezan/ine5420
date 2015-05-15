#ifndef __MAINWINDOWH
#define __MAINWINDOWH

#include <gtkmm.h>
#include <iostream>
#include <memory>
#include "utils/objIO.h"
#include "cg/World.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/tools.h"
#include "ui/Toolbox.h"
#include "ui/dialogs.h"
#include "ui/GtkUIViewport.h"

class MainWindow : public Gtk::Window {
	private:
		std::shared_ptr<CG::World> _world;
		CG::Window _window;
		GtkUIViewport _viewport;

		Toolbox _toolbox;
		Gtk::Box _mainBox;
		Glib::RefPtr<Gtk::ActionGroup> _actionGroup;
		Glib::RefPtr<Gtk::UIManager> _uiManager;
    std::shared_ptr<CG::Tool> tool;

	public:
		MainWindow();
    void alert(CGException& e);

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
    void on_newSurface();
		void on_action_file_open();
		void on_action_file_save();

		// Keyboard handlers
		bool on_key_press_event(GdkEventKey* event);

    // Mouse handlers
    bool on_scroll_event(GdkEventScroll* event);
    bool on_button_press_event(GdkEventButton* event);
    bool on_button_release_event(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);
};

#endif
