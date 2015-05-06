#include "cg/Window.h"
#include <ctgmath>

#include <iostream>

namespace CG {

Window:: Window(double cx, double cy, double width, double height, double thetaZ, double thetaX, double thetaY)
        : _center(cx, cy, -1), _width(width), _height(height), _thetaZ(thetaZ), _thetaX(thetaX), _thetaY(thetaY) {
    updateMatrix();
}

bool Window::zoom(double step) {
    // Maximum zoom reached
    if (_width + step <= 0 ||  _height + step <= 0)
        return false;

    _width += step;
    _height += step;
    return true;
}

void Window::move(double dx, double dy, double dz) {
    Coordinate c(dx, dy, dz);
    c *= Transformation::newRx(-_thetaX) * Transformation::newRy(-_thetaY) * Transformation::newRz(-_thetaZ);
    _center.x -= c.x;
    _center.y -= c.y;
    _center.z -= c.z;
}

void Window::updateMatrix() {
    _wo2wiMatrix = Transformation();
    _wo2wiMatrix *= Transformation::newTranslation(-_center.x, -_center.y, -_center.z);
    _wo2wiMatrix *= Transformation::newRx(_thetaX);
    _wo2wiMatrix *= Transformation::newRy(_thetaY);
    _wo2wiMatrix *= Transformation::newRz(_thetaZ);
    _wo2wiMatrix *= Transformation::newScaling(1.0/_width, 1.0/_height, 1.0);
}

}
