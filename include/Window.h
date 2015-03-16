#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

namespace CG {

  class Window {
	  public:
		  Window(float, float, float, float);
		  Window() = default;

		  float xmin() { return _xmin; }
		  float ymin() { return _ymin; }
		  float xmax() { return _xmax; }
		  float ymax() { return _ymax; }

		  void dx(float d) { _xmin += d; _xmax += d; }
		  void dy(float d) { _ymin += d; _ymax += d; }
      void zoom(float step);

	  private:
		  float _xmin, _ymin, _xmax, _ymax;
  };

}

#endif
