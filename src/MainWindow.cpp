#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

#include "geometrics.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  CG::Window window(-10, -10, 10, 10);
  CG::DisplayFile displayFile;
  
  displayFile.add("P1",	CG::GPoint(3, 2));
  displayFile.add("Xaxis", CG::GLine(-1000, 0, 1000, 0));
  displayFile.add("Yaxis", CG::GLine(0, -1000, 0, 1000));
  displayFile.add("Line1", CG::GLine(-20, -4, 5, 3));
  displayFile.add("Line2", CG::GLine(-5, 5, 5, -5));

  viewport.displayFile(displayFile);
  viewport.window(window);

  add(viewport);
  viewport.show();
}

