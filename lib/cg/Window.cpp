#include "cg/Window.h"

namespace CG {

  Window:: Window(double cx, double cy, double width, double height, double theta)
	  : _center(cx, cy), _width(width), _height(height), _theta(theta) {
	  _wo2wiMatrix *= Transformation::newTranslation(-cx, -cy);
	  _wo2wiMatrix *= Transformation::newRotationAroundOrigin(theta);
	  _wo2wiMatrix *= Transformation::newScaling(1.0/width, 1.0/height);
  }

  void Window::zoom(double step) {
    // Maximum zoom reached
    if (_width + step <= 0 ||  _height + step <= 0) 
      return;

	_width += step;
	_height += step;
  }

}
