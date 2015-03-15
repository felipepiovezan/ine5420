#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

MainWindow::MainWindow() {
  init_viewport();

  // Layouting
  set_title("Computer Graphics Interative System");
  set_border_width(10);

  add(_mainBox);
  _mainBox.set_spacing(10);
  _mainBox.show();

  _mainBox.pack_start(_toolbox, Gtk::PACK_SHRINK);
  _toolbox.set_size_request(200, 0);
  _mainBox.pack_end(_viewport, Gtk::PACK_EXPAND_WIDGET);
  _viewport.set_size_request(550, 550);

  _toolbox.show();
  _viewport.show();
}

void MainWindow::init_viewport(){
  CG::Window window(-10, -10, 10, 10);
  _viewport.window(window);

  CG::DisplayFile displayFile;
  displayFile.add("P1",	CG::GPoint(3, 2));
  displayFile.add("P2",	CG::GPoint(2, 2));
  displayFile.add("Xaxis", CG::GLine(-1000, 0, 1000, 0));
  displayFile.add("Yaxis", CG::GLine(0, -1000, 0, 1000));
  displayFile.add("Line1", CG::GLine(-20, -4, 5, 3));
  displayFile.add("Line2", CG::GLine(-5, 5, 5, -5));
  _viewport.displayFile(displayFile);
}
