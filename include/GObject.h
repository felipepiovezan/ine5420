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

    typedef std::vector<Point>::iterator PointIterator;

    PointIterator begin() {
      return points.begin();
    }

    PointIterator end() {
      return points.end();
    }

  protected:
    std::vector<Point> points;
  };

}

#endif
