#ifndef CG_GOBJECT_H_
#define CG_GOBJECT_H_

#include <string>
#include <vector>
#include "Point.h"

namespace CG {

  /**
   * Geometrical Object
   */
  class GObject {
  public:
    GObject();
    void addPoint(Point p);

    std::string name;

  protected:
    std::vector<Point> points;
  };

}

#endif
