#include <gtkmm.h>
#include "Canvas.h"

class MainWindow : public Gtk::Window {
public:
  MainWindow();
  ~MainWindow();

  Canvas *canvas;
};
