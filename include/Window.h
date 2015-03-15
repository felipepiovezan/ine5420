#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

namespace CG {

  class Window {
	  public:
		  Window(float, float, float, float);
		  Window() = default;

		  void scaleFactor(float factor = 1) { _scaleFactor = factor;}
		  void dx(float d) {_dx = d;}
		  void dy(float d) {_dy = d;}

		  float xmin(){return (_xmin + _dx) * _scaleFactor;}
		  float ymin(){return (_ymin + _dy) * _scaleFactor;}
		  float xmax(){return (_xmax + _dx) * _scaleFactor;}
		  float ymax(){return (_ymax + _dy) * _scaleFactor;}

	  private:
		  float _xmin, _ymin, _xmax, _ymax;
		  float _scaleFactor = 1;
		  float _dx = 0, _dy = 0;
  };

}

#endif
