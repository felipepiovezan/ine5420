#include "GObject.h"

namespace CG {

  GObject::GObject() {

  }

  void GObject::addPoint(Point p) {
    points.push_back(p);
  }

}
