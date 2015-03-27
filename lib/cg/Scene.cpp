#include "cg/Scene.h"

#include "cg/Transformations.h"
#include <cassert>

namespace CG {

  Scene::Scene(DrawingContext& ctx) :
    window(0, 0, 10, 10, 0),
    displayFile(),
    viewport(ctx, window, displayFile)
  {
    viewport.redraw();
    notifyObjectChange();
    notifyWindowChange();
  }

  void Scene::addObject(std::string name, const GObject& obj) {
    displayFile.add(name, obj, window.wo2wiMatrix());
    viewport.redraw();
    notifyObjectChange();
  }

  void Scene::createPoint(std::string name, Color color, Coordinate c) {
    GPoint point(c);
    point.color = color;
    addObject(name, point);
  }

  void Scene::createLine(std::string name, Color color, Coordinate c1, Coordinate c2) {
    GLine line(c1, c2);
    line.color = color;
    addObject(name, line);
  }

  void Scene::createPolygon(std::string name, Color color, GObject::Coordinates coordinates) {
    GPolygon polygon(coordinates);
    polygon.color = color;
    addObject(name, polygon);
  }

  void Scene::translateObject(const std::string &name, double dx, double dy) {
    auto itWindow = displayFile.findWindowObject(name);
  	auto itWorld = displayFile.findWorldObject(name);
  	assert(displayFile.isValidWindowIterator(itWindow) && displayFile.isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

    Transformation transformation = Transformation::newTranslation(dx, dy);
    worldObject.transform(transformation);
    //TODO: transform these two lines into a single operator * line
    windowObject = worldObject;
    windowObject.transform(window.wo2wiMatrix());
  }

  void Scene::scaleObject(const std::string &name, double sx, double sy) {
    auto itWindow = displayFile.findWindowObject(name);
  	auto itWorld = displayFile.findWorldObject(name);
  	assert(displayFile.isValidWindowIterator(itWindow) && displayFile.isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

    Transformation transformation = Transformation::newScalingAroundObjCenter(sx, sy, worldObject);

    worldObject.transform(transformation);
    //TODO: transform these two lines into a single operator * line
    windowObject = worldObject;
    windowObject.transform(window.wo2wiMatrix());
  }

  void Scene::rotateObject(const std::string &name, double theta, const Coordinate& rotationCenter) {
    auto itWindow = displayFile.findWindowObject(name);
  	auto itWorld = displayFile.findWorldObject(name);
  	assert(displayFile.isValidWindowIterator(itWindow) && displayFile.isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

  	Transformation transformation = Transformation::newRotationAroundPoint(Transformation::toRadians(theta), rotationCenter);

    worldObject.transform(transformation);
    //TODO: transform these two lines into a single operator * line
    windowObject = worldObject;
    windowObject.transform(window.wo2wiMatrix());
  }

  void Scene::rotateObject(const std::string &name, double theta) {
    // If no rotationCenter was provided, consider the center as the object center
    auto itWindow = displayFile.findWindowObject(name);
  	auto itWorld = displayFile.findWorldObject(name);
  	assert(displayFile.isValidWindowIterator(itWindow) && displayFile.isValidWorldIterator(itWorld));

  	auto &worldObject = itWorld->second;
  	auto &windowObject = itWindow->second;

  	Transformation transformation = Transformation::newRotationAroundObjCenter(Transformation::toRadians(theta), worldObject);

    worldObject.transform(transformation);
    //TODO: transform these two lines into a single operator * line
    windowObject = worldObject;
    windowObject.transform(window.wo2wiMatrix());
  }

  void Scene::changeWindowZoom(double step){
  	window.zoom(step);
  	window.updateMatrix();
  	displayFile.updateWindowCoords(window.wo2wiMatrix());
    viewport.redraw();
    notifyWindowChange();
  }

  void Scene::changeWindowPosition(double sx, double sy){
  	window.move(sx, sy);
  	window.updateMatrix();
  	displayFile.updateWindowCoords(window.wo2wiMatrix());
    viewport.redraw();
    notifyWindowChange();
  }

  void Scene::rotateWindow(double theta){
  	window.rotate(Transformation::toRadians(theta));
  	window.updateMatrix();
  	displayFile.updateWindowCoords(window.wo2wiMatrix());
    viewport.redraw();
    notifyWindowChange();
  }

  void Scene::notifyObjectChange() {
    for (auto &it : listeners)
      it->onObjectChange(displayFile);
  }

  void Scene::notifyWindowChange() {
    for (auto &it : listeners)
      it->onWindowChange(window);
  }

  void Scene::addListener(Listener& listener) {
    listeners.push_back(&listener);
  }
}
