#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

#include "cg/GObject.h"

namespace CG {

  class Window {
	  public:
		  Window(double cx, double cy, double width, double height, double theta);

		  double width() const { return _width; }
		  double height() const { return _height; }
		  double theta() const { return _theta; }
		  const Transformation& wo2wiMatrix() const {return _wo2wiMatrix;}
		  int xmin() const { return -1;}
		  int xmax() const { return  1;}
		  int ymin() const { return -1;}
		  int ymax() const { return  1;}

		  //methods related to window transformations
		  void updateMatrix();
		  void move(double dx, double dy);
		  bool zoom(double step);
		  void rotate(double theta) {_theta += theta;}

	  private:
		  Coordinate _center;
		  double _width, _height, _theta;
		  Transformation _wo2wiMatrix;
  };

}

#endif
