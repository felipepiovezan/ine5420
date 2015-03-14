#include "GLine.h"

namespace CG {

  GLine::GLine(int x1, int y1, int x2, int y2) {
    addCoordinate(Coordinate(x1, y1));
    addCoordinate(Coordinate(x2, y2));
  }

}
