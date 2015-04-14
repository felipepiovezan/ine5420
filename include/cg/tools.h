#ifndef CG_TOOLS_H_
#define CG_TOOLS_H_

#include "cg/Viewport.h"

namespace CG {

class Tool {
 public:
  virtual void init(double x, double y) {}
  virtual void update(double x, double y) {}
  virtual void end(double x, double y) {}
  virtual void cancel(double x, double y) {}
};

/**
 * The default tool. Used to move the window and select objects (TODO)
 */
class HandTool : public Tool {
 public:
  HandTool(Viewport& viewport) : viewport(&viewport) {}

  void init(double x, double y);
  void update(double x, double y);

 private:
  Viewport* viewport;
  double x_init, y_init;
};

}  // namespace CG

#endif
