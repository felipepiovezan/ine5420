#ifndef CG_WINDOW_H_
#define CG_WINDOW_H_

#include "cg/objects.h"

namespace CG {

class Window {
public:
    Window(double cx, double cy, double cz, double width, double height, double thetaX = 0, double thetaY = 0, double thetaZ = 0);

    double width() const {return _width;}
    double height() const {return _height;}
    double thetaX() const {return _thetaX;}
    double thetaY() const {return _thetaY;}
    double thetaZ() const {return _thetaZ;}
    double d() const {return _d;}
    int xmin() const {return -1;}
    int xmax() const {return  1;}
    int ymin() const {return -1;}
    int ymax() const {return  1;}
    const Transformation& wo2wiMatrix() const {return _wo2wiMatrix;}

    //methods related to window transformations
    void updateMatrix();
    void move(double dx, double dy, double dz);
    bool zoom(double step);
    void rotateX(double theta) {_thetaX += theta;}
    void rotateY(double theta) {_thetaY += theta;}
    void rotateZ(double theta) {_thetaZ += theta;}

private:
    Coordinate _center;
    double _width, _height, _thetaX, _thetaY, _thetaZ;
    Transformation _wo2wiMatrix;
    double _d = 2.0; //center of projection
};

}

#endif
