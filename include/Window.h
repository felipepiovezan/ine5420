#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

namespace CG {

  class Window {
  public:
    Window(int, int, int, int);
    int xmin, ymin, xmax, ymax;
  };

}

#endif
