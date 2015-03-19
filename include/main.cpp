#include <gtkmm.h>
#include "ui/MainWindow.h"

int main(int argc, char **argv) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  MainWindow window;
  return app->run(window);
}
