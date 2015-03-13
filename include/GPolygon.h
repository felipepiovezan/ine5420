#ifndef GPOLYGON_H_
#define GPOLYGON_H_

#include <string>
#include "GObject.h"

namespace CG {

  class GPolygon : public CG::GObject {
  public:
    GPolygon(std::string name);
  };

}

#endif
