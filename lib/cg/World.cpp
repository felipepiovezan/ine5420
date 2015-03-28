#include "cg/World.h"
#include "cg/Transformations.h"
#include <cassert>

namespace CG {

  void World::addObject(std::string name, const GObject& obj) {
    _worldObjects.add(name, obj);
    notifyObjectCreation(name, obj);
  }

  void World::addObject(std::string baseName, const std::vector<GObject>& objVector) {
    int i=0;
    for(const auto &obj : objVector) {
      std::string name = baseName + std::to_string(i++);
      _worldObjects.add(name, obj);
      notifyObjectCreation(name, obj);
    }
  }

  void World::createPoint(std::string name, Color color, Coordinate c) {
    GPoint point(c);
    point.color = color;
    addObject(name, point);
  }

  void World::createLine(std::string name, Color color, Coordinate c1, Coordinate c2) {
    GLine line(c1, c2);
    line.color = color;
    addObject(name, line);
  }

  void World::createPolygon(std::string name, Color color, GObject::Coordinates coordinates) {
    GPolygon polygon(coordinates);
    polygon.color = color;
    addObject(name, polygon);
  }

  void World::translateObject(const std::string &name, double dx, double dy) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject.transform(Transformation::newTranslation(dx, dy));
    notifyObjectChange(name, worldObject);
  }

  void World::scaleObject(const std::string &name, double sx, double sy) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject.transform(Transformation::newScalingAroundObjCenter(sx, sy, worldObject));
    notifyObjectChange(name, worldObject);
  }

  void World::rotateObject(const std::string &name, double theta, const Coordinate& rotationCenter) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
    auto &worldObject = itWorld->second;
    worldObject.transform(Transformation::newRotationAroundPoint(Transformation::toRadians(theta), rotationCenter));
    notifyObjectChange(name, worldObject);
  }

  void World::rotateObject(const std::string &name, double theta) {
    // If no rotationCenter was provided, consider the center as the object center
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject.transform(Transformation::newRotationAroundObjCenter(Transformation::toRadians(theta), worldObject));
    notifyObjectChange(name, worldObject);
  }

  void World::addListener(WorldListener& listener) {
    _listeners.push_back(&listener);
  }

  void World::notifyObjectCreation(const std::string& name, const GObject& object) const {
    for (auto it : _listeners)
      it->onObjectCreation(name, object);
  }

  void World::notifyObjectChange(const std::string& name, const GObject& object) const {
    for (auto it : _listeners)
      it->onObjectChange(name, object);
  }
}
