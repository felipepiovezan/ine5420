#ifndef CG_GPOLYGON_H_
#define CG_GPOLYGON_H_

#include <string>
#include "GObject.h"

namespace CG {

  class GPolygon : public CG::GObject {
  public:
    GPolygon(std::string name);
  };

}

#endif
