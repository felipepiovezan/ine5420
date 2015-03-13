#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

#include "geometrics.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  CG::Window *window = new CG::Window(-5, -5, 5, 5);
  CG::DisplayFile *displayFile = new CG::DisplayFile();

  CG::GPoint *p1 = new CG::GPoint(30, 20);
  CG::GLine *line1 = new CG::GLine(-2, -4, 500, 300);
  displayFile->add("P1", p1);
  displayFile->add("Line1", line1);

  canvas = new Canvas(window, displayFile);

  add(*canvas);
  canvas->show();
}

MainWindow::~MainWindow() {
  delete canvas;
}
