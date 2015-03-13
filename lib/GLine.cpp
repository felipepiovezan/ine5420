#include "GLine.h"

namespace CG {

  GLine::GLine(int x1, int y1, int x2, int y2) {
    addPoint(Point(x1, y1));
    addPoint(Point(x2, y2));
  }

}
