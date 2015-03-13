#ifndef CG_GOBJECT_H_
#define CG_GOBJECT_H_

#include <vector>
#include "Point.h"

namespace CG {

  /**
   * Geometrical Object
   */
  class GObject {
  public:
    void addPoint(Point p);

  protected:
    std::vector<Point> points;
  };

}

#endif
