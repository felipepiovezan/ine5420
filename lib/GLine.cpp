#include "GLine.h"

namespace CG {

  GLine::GLine(std::string name, int x1, int y1, int x2, int y2) {
    this->name = name;
    addPoint(Point(x1, y1));
    addPoint(Point(x2, y2));
  }

}
