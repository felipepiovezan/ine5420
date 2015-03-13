#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

#include "geometrics.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  CG::Window window(-5, -5, 5, 5);
  CG::DisplayFile displayFile;

  CG::GPoint p1(3, 2);
  CG::GLine line1(-2, -4, 5, 3);
  displayFile.add("P1", p1);
  displayFile.add("Line1", line1);

  canvas = new Canvas(&window, &displayFile);

  add(*canvas);
  canvas->show();
}

MainWindow::~MainWindow() {
  delete canvas;
}
