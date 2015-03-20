#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

namespace CG {

  class Window {
	  public:
		  Window(double, double, double, double);
		  Window() = default;

		  double xmin() { return _xmin; }
		  double ymin() { return _ymin; }
		  double xmax() { return _xmax; }
		  double ymax() { return _ymax; }

		  void dx(double d) { _xmin += d; _xmax += d; }
		  void dy(double d) { _ymin += d; _ymax += d; }
      void zoom(double step);

	  private:
		  double _xmin, _ymin, _xmax, _ymax;
  };

}

#endif
