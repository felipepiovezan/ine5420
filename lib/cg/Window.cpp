#include "cg/Window.h"

namespace CG {

  Window::Window(double xmin, double ymin, double xmax, double ymax)
    : _xmin(xmin), _ymin(ymin), _xmax(xmax), _ymax(ymax) {

  }

  void Window::zoom(double step) {
    if (_xmin + step >= _xmax - step || _ymin + step >= _ymax - step) {
      // Maximum zoom reached
      return;
    }

    _xmin += step;
    _ymin += step;
    _xmax -= step;
    _ymax -= step;
  }

}
