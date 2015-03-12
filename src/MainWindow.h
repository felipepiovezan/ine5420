#include <gtkmm.h>
#include "Canvas.h"

class MainWindow : public Gtk::Window {
public:
  MainWindow();

  Canvas canvas;
};
