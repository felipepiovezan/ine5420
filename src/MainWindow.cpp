#include "MainWindow.h"

MainWindow::MainWindow() {
  set_default_size(600, 480);
  set_title("Testing");
  set_border_width(10);

  add(canvas);
  canvas.show();
}
