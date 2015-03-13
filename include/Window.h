#ifndef WINDOW_H_
#define WINDOW_H_

namespace CG {

  class Window {
  public:
    Window(int, int, int, int);
    int xmin, ymin, xmax, ymax;
  };

}

#endif
