#ifndef CG_GLINE_H_
#define CG_GLINE_H_

#include <string>
#include "GObject.h"

namespace CG {

  class GLine : public CG::GObject {
  public:
    GLine(std::string name, int x1, int y1, int x2, int y2);
  };

}

#endif
