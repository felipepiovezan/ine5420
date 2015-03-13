#ifndef CG_GPOINT_H_
#define CG_GPOINT_H_

#include <string>
#include "GObject.h"

namespace CG {

  class GPoint : public CG::GObject {
  public:
    GPoint(int x, int y);
  };

}

#endif
