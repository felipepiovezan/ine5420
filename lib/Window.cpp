#include "Window.h"

namespace CG {

  Window::Window(float xmin, float ymin, float xmax, float ymax)
    : _xmin(xmin), _ymin(ymin), _xmax(xmax), _ymax(ymax) {

  }

  void Window::zoom(float step) {
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
