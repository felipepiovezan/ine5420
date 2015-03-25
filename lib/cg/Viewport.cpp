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

  // TODO: remove transformations from here

  void Viewport::applyTranslation(const std::string &name, double dx, double dy){
  	auto itWindow = displayFile->findWindowObject(name);
  	auto itWorld = displayFile->findWorldObject(name);
  	assert(displayFile->isValidWindowIterator(itWindow) && displayFile->isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

      CG::Transformation transformation = CG::Transformation::newTranslation(dx, dy);
      worldObject.transform(transformation);
      //TODO: transform these two lines into a single operator * line
      windowObject = worldObject;
      windowObject.transform(window->wo2wiMatrix());
  }

  void Viewport::applyScaling(const std::string &name, double sx, double sy){
  	auto itWindow = displayFile->findWindowObject(name);
  	auto itWorld = displayFile->findWorldObject(name);
  	assert(displayFile->isValidWindowIterator(itWindow) && displayFile->isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

  	CG::Coordinate center = worldObject.center();

      //TODO: use the transformation builder instead of multiplying it here.
      CG::Transformation transformation = CG::Transformation::newTranslation(-center.x, -center.y);
      transformation *= CG::Transformation::newScaling(sx, sy);
      transformation *= CG::Transformation::newTranslation(center.x, center.y);

      worldObject.transform(transformation);
      //TODO: transform these two lines into a single operator * line
      windowObject = worldObject;
      windowObject.transform(window->wo2wiMatrix());
  }

  void Viewport::applyRotation(const std::string &name, double theta, const CG::Coordinate &rotationCenter){
  	auto itWindow = displayFile->findWindowObject(name);
  	auto itWorld = displayFile->findWorldObject(name);
  	assert(displayFile->isValidWindowIterator(itWindow) && displayFile->isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

  	CG::Transformation transformation = CG::Transformation::newRotationAroundPoint(CG::Transformation::toRadians(theta), rotationCenter);

      worldObject.transform(transformation);
      //TODO: transform these two lines into a single operator * line
      windowObject = worldObject;
      windowObject.transform(window->wo2wiMatrix());
  }

}
