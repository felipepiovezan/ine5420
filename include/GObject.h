#ifndef CG_GOBJECT_H_
#define CG_GOBJECT_H_

#include <vector>
#include "Coordinate.h"

namespace CG {

  /**
   * Geometrical Object
   */
  class GObject {
  public:
    void addCoordinate(Coordinate p);

    typedef std::vector<Coordinate>::iterator CoordinateIterator;

    CoordinateIterator begin() {
      return coordinates.begin();
    }

    CoordinateIterator end() {
      return coordinates.end();
    }

  protected:
    std::vector<Coordinate> coordinates;
  };

}

#endif
