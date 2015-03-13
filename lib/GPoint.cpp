#include "GPoint.h"

namespace CG {

  GPoint::GPoint(std::string name, int x, int y) {
    this->name = name;
    addPoint(Point(x, y));
  }

}
