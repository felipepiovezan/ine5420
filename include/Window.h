#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

namespace CG {

  class Window {
	  public:
		  Window(float, float, float, float);
		  Window() = default;

		  float xmin, ymin, xmax, ymax;
  };

}

#endif
