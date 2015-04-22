#include "cg/tools.h"

namespace CG {

void HandTool::init(double x, double y) {
  x_init = viewport->screenToWindowTransformX(x);
  y_init = viewport->screenToWindowTransformY(y);
}

void HandTool::update(double x, double y) {
  double x_window = viewport->screenToWindowTransformX(x);
  double y_window = viewport->screenToWindowTransformY(y);
  viewport->changeWindowPosition(x_window - x_init, y_init - y_window, 0);
  x_init = x_window;
  y_init = y_window;
}

}
