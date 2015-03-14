#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

#include "geometrics.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  CG::Window *window = new CG::Window(-10, -10, 10, 10);
  CG::DisplayFile *displayFile = new CG::DisplayFile();

  CG::GPoint *p1 = new CG::GPoint(3, 2);
  CG::GLine *line1 = new CG::GLine(-2, -4, 5, 3);
  CG::GLine *line2 = new CG::GLine(-5, 5, 5, -5);
  displayFile->add("P1", p1);
  displayFile->add("Line1", line1);
  displayFile->add("Line2", line2);

  viewport = new Viewport(window, displayFile);

  add(*viewport);
  viewport->show();
}

MainWindow::~MainWindow() {
  delete viewport;
}
