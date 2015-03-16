#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

namespace CG {

  class Window {
	  public:
		  Window(float, float, float, float);
		  Window() = default;

		  float xmin() { return (_xmin + _dx); }
		  float ymin() { return (_ymin + _dy); }
		  float xmax() { return (_xmax + _dx); }
		  float ymax() { return (_ymax + _dy); }

		  void dx(float d) {_dx = d;}
		  void dy(float d) {_dy = d;}

      void zoom(float step);

	  private:
		  float _xmin, _ymin, _xmax, _ymax;
		  float _scaleFactor = 1;
		  float _dx = 0, _dy = 0;
  };

}

#endif
