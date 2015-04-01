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

  bool LBLineClipping::clipLine(GLine& l, ClippingRect& rect) {
    assert(l.numPoints() == 2);

    auto c1 = l.coordinates()[0];
    auto c2 = l.coordinates()[1];
    auto delta = c2 - c1;

    double u1 = 0.0;
    double u2 = 1.0;
    double p, q, r;

    // Check left, right, bottom and top edges, respectively
    for(int edge = 0; edge < 4; edge++) {
      if      (edge == 0) { p = -delta.x; q = c1.x - rect.minX; }
      else if (edge == 1) { p =  delta.x; q = rect.maxX - c1.x; }
      else if (edge == 2) { p = -delta.y; q = c1.y - rect.minY; }
      else if (edge == 3) { p =  delta.y; q = rect.maxY - c1.y; }

      if (p == 0 && q < 0) {
        // Line parallel to edge and completely outside
        l.clear();
        return false;
      }

      r = q/p;
      if (p < 0) { // line proceeds outside to inside
        if (r > u2) {
          l.clear();
          return false;
        } else if (r > u1) {
          u1 = r;
        }
      } else if (p > 0) { // line proceeds inside to outside
        if (r < u1) {
          l.clear();
          return false;
        } else if (r < u2) {
          u2 = r;
        }
      }
    }

    Coordinate nc1(c1.x + u1 * delta.x, c1.y + u1 * delta.y);
    Coordinate nc2(c1.x + u2 * delta.x, c1.y + u2 * delta.y);
    l = GLine(nc1, nc2);

    return true;
  }

}
