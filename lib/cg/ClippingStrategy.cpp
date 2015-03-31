#include "cg/ClippingStrategy.h"

#include <cassert>
#include <iostream>

namespace CG {

  bool SimplePointClipping::clipPoint(GPoint& p, ClippingRect& rect) {
    assert(p.numPoints() == 1);

    auto c = p.coordinates()[0];
    bool onScreen = c.x >= rect.minX && c.x <= rect.maxX &&
                    c.y >= rect.minY && c.y <= rect.maxY;

    if (!onScreen)
      p.clear();

    return !onScreen;
  }
}
