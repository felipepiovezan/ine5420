#include "cg/Viewport.h"

namespace CG {

  void Viewport::onContextChange() {
    for(const auto &it : displayFile->windowObjects()){
  		drawObject(it.second);
  	}
  }

  void Viewport::drawObject(const GObject& obj) {
    if (obj.numPoints() == 0)
      return;

    // Generate the viewport coordinates
    CG::GObject::Coordinates vwCoordinates = transformCoordinates(obj.coordinates());

    if (obj.numPoints() == 1) {
      ctx->drawPoint(vwCoordinates[0], obj.color);
      return;
    }

    if (obj.numPoints() == 2) {
      ctx->drawLine(vwCoordinates[0], vwCoordinates[1], obj.color);
      return;
    }

    ctx->drawPolygon(vwCoordinates, obj.color);
  }

  Coordinate Viewport::transformCoordinate(const Coordinate& c) const {
    int width = ctx->getWidth();
    int height = ctx->getHeight();
    double x = width * (c.x - window->xmin()) / (window->xmax() - window->xmin());
    double y = height * (1 - ((c.y - window->ymin()) / (window->ymax() - window->ymin())));
    return Coordinate(x, y);
  }

  GObject::Coordinates Viewport::transformCoordinates(GObject::Coordinates coords) const {
    CG::GObject::Coordinates vwCoordinates;
    for (auto &c : coords) {
      vwCoordinates.push_back(transformCoordinate(c));
    }

    return vwCoordinates;
  }

}
