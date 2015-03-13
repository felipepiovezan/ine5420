#ifndef GPOINT_H_
#define GPOINT_H_

#include <string>
#include "GObject.h"

namespace CG {

  class GPoint : public CG::GObject {
  public:
    GPoint(std::string name, int x, int y);
  };

}

#endif
