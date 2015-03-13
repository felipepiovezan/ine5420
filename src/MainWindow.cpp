#include "MainWindow.h"
#include "Window.h"
#include "DisplayFile.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  CG::Window window(-5, -5, 5, 5);
  CG::DisplayFile displayFile();

  //Canvas(&window, &dfile);

  add(canvas);
  canvas.show();
}
