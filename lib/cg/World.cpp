#include "cg/World.h"
#include "cg/Transformations.h"
#include <cassert>
#include <iostream>

namespace CG {

  void World::addObject(std::string name, ObjRef obj) {
    _worldObjects.add(name, obj);
    notifyObjectCreation(name, obj);
  }

  void World::addObject(std::string baseName, const std::vector<ObjRef>& objVector) {
    int i=0;
    for(const auto &obj : objVector) {
      std::string name = baseName + std::to_string(i++);
      _worldObjects.add(name, obj);
    }
    notifyObjectCreation(baseName, objVector);
  }

  void World::createPoint(std::string name, Decoration decoration, Coordinate c) {
	ObjRef point(new GPoint (c));
    point->decoration = decoration;
    addObject(name, point);
  }

  void World::createLine(std::string name, Decoration decoration, Coordinate c1, Coordinate c2) {
	ObjRef line( new GLine(c1, c2));
    line->decoration = decoration;
    addObject(name, line);
  }

  void World::createPolygon(std::string name, Decoration decoration, GObject::Coordinates coordinates) {
	ObjRef polygon(new GPolygon(coordinates));
    polygon->decoration = decoration;
    addObject(name, polygon);
  }

  void World::createCurve(std::string name, Decoration decoration, GObject::Coordinates coordinates) {
	  //todo change to curve.
	  ObjRef polygon(new GPolygon(coordinates));
      polygon->decoration = decoration;
      addObject(name, polygon);
  }

  void World::removeObject(const std::string &name) {
    assert(_worldObjects.exists(name));
    _worldObjects.remove(name);
    notifyObjectRemoval(name);
  }

  void World::translateObject(const std::string &name, double dx, double dy) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject->transform(Transformation::newTranslation(dx, dy));
    notifyObjectChange(name, worldObject);
  }

  void World::scaleObject(const std::string &name, double sx, double sy) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject->transform(Transformation::newScalingAroundObjCenter(sx, sy, *worldObject));
    notifyObjectChange(name, worldObject);
  }

  void World::rotateObject(const std::string &name, double theta, const Coordinate& rotationCenter) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
    auto &worldObject = itWorld->second;
    worldObject->transform(Transformation::newRotationAroundPoint(Transformation::toRadians(theta), rotationCenter));
    notifyObjectChange(name, worldObject);
  }

  void World::rotateObject(const std::string &name, double theta) {
    // If no rotationCenter was provided, consider the center as the object center
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject->transform(Transformation::newRotationAroundObjCenter(Transformation::toRadians(theta), *worldObject));
    notifyObjectChange(name, worldObject);
  }

  void World::addListener(WorldListener& listener) {
    _listeners.push_back(&listener);
  }

  void World::notifyObjectCreation(const std::string& name, ObjRef object) const {
    for (auto it : _listeners)
      it->onObjectCreation(name, object);
  }
  void World::notifyObjectCreation(const std::string& baseName, const std::vector<ObjRef>& objects) const{
	for (auto it : _listeners)
		it->onObjectCreation(baseName, objects);
  }
  void World::notifyObjectChange(const std::string& name, ObjRef object) const {
    for (auto it : _listeners)
      it->onObjectChange(name, object);
  }

  void World::notifyObjectRemoval(const std::string& name) const {
    for (auto it : _listeners)
      it->onObjectRemoval(name);
  }
}
