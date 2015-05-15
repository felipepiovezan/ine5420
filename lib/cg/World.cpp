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

  void World::createBezierCurve(std::string name, Decoration decoration, GObject::Coordinates coordinates) {
	  ObjRef curve(new BezierCurve(coordinates));
    curve->decoration = decoration;
    addObject(name, curve);
  }

  void World::createSplineCurve(std::string name, Decoration decoration, GObject::Coordinates coordinates) {
    ObjRef curve(new SplineCurve(coordinates));
    curve->decoration = decoration;
    addObject(name, curve);
  }

  void World::createBezierSurface(std::string name, Decoration decoration, GObject::Coordinates coordinates){
	  ObjRef surface(new GSurface(GSurface::BEZIER, coordinates));
	  surface->decoration = decoration;
	  addObject(name, surface);
  }

  void World::createSplineSurface(std::string name, Decoration decoration, GObject::Coordinates coordinates){
  	  ObjRef surface(new GSurface(GSurface::B_SPLINE, coordinates));
  	  surface->decoration = decoration;
  	  addObject(name, surface);
    }

  void World::removeObject(const std::string &name) {
    assert(_worldObjects.exists(name));
    _worldObjects.remove(name);
    notifyObjectRemoval(name);
  }

  void World::translateObject(const std::string &name, double dx, double dy, double dz) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject->transform(Transformation::newTranslation(dx, dy, dz));
    notifyObjectChange(name, worldObject);
  }

  void World::scaleObject(const std::string &name, double sx, double sy, double sz) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;
    worldObject->transform(Transformation::newScalingAroundObjCenter(sx, sy, sz, worldObject->center()));
    notifyObjectChange(name, worldObject);
  }

  void World::rotateObject(const std::string &name, double thetaX, double thetaY, double thetaZ, const Coordinate& rotationCenter) {
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
    auto &worldObject = itWorld->second;

    double radX = Transformation::toRadians(thetaX);
    double radY = Transformation::toRadians(thetaY);
    double radZ = Transformation::toRadians(thetaZ);
    worldObject->transform(Transformation::newRotation(radX, radY, radZ, rotationCenter));
    notifyObjectChange(name, worldObject);
  }

  void World::rotateObject(const std::string &name, double thetaX, double thetaY, double thetaZ) {
    // If no rotationCenter was provided, consider the center as the object center
  	auto itWorld = _worldObjects.findObject(name);
  	assert(_worldObjects.isValidIterator(itWorld));
  	auto &worldObject = itWorld->second;

    double radX = Transformation::toRadians(thetaX);
    double radY = Transformation::toRadians(thetaY);
    double radZ = Transformation::toRadians(thetaZ);
    worldObject->transform(Transformation::newRotation(radX, radY, radZ, worldObject->center()));
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
