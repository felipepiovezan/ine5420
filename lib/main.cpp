#include <gtkmm.h>
#include "ui/MainWindow.h"
//#include "cg/objIO.h"

int main(int argc, char **argv) {
	//ObjReader("obj.obj");

  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  MainWindow window;
  return app->run(window);
}
