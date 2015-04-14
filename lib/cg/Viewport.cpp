#include "cg/Viewport.h"

#include<iostream>
#include <cassert>

#include <ctime>
namespace CG {

 Coordinate Viewport::transformCoordinate(const Coordinate& c) const {
   int width = getWidth();
   int height = getHeight();
   double x = width * (c.x - _window.xmin()) / (_window.xmax() - _window.xmin());
   double y = height * (1 - ((c.y - _window.ymin()) / (_window.ymax() - _window.ymin())));
   return Coordinate(x, y);
 }

 GObject::Coordinates Viewport::transformCoordinates(const GObject::Coordinates& coords) const {
   CG::GObject::Coordinates vwCoordinates;
   for (const auto &c : coords)
     vwCoordinates.push_back(transformCoordinate(c));

   return vwCoordinates;
 }

  double Viewport::screenToWindowTransformX(double x_screen) {
    int width = getWidth();
    return (x_screen / width) * _window.width() * (_window.xmax() - _window.xmin());
  }

  double Viewport::screenToWindowTransformY(double y_screen) {
    int height = getHeight();
    return (y_screen / height) * _window.height() * (_window.ymax() - _window.ymin());
  }

	void Viewport::changeWindowZoom(double step){
		if(_window.zoom(step)){
			_window.updateMatrix();
			transformAndClipAll(_window.wo2wiMatrix());
			redraw();
		}
	}

	void Viewport::changeWindowPosition(double sx, double sy){
		_window.move(sx, sy);
		_window.updateMatrix();
		transformAndClipAll(_window.wo2wiMatrix());
		redraw();
	}

	void Viewport::rotateWindow(double theta){
		_window.rotate(Transformation::toRadians(theta));
		_window.updateMatrix();
		transformAndClipAll(_window.wo2wiMatrix());
		redraw();
	}

  void Viewport::onObjectCreation(const std::string& name, const GObject& object) {
    assert(!_windowObjects.exists(name));
    auto &windowObj = _windowObjects.add(name, object);
    transformAndClip(windowObj, _window.wo2wiMatrix());
    drawObject(windowObj); // Draw only the inserted object
  }

  void Viewport::onObjectCreation(const std::string& baseName, const std::vector<GObject> &objects) {
	  int i=0;
	  for(const auto &obj : objects) {
		  auto name = baseName + std::to_string(i++);
		  assert(!_windowObjects.exists(name));
		  auto &windowObj = _windowObjects.add(name, obj);
	      transformAndClip(windowObj, _window.wo2wiMatrix());
	  }
      redraw();
  }

  void Viewport::onObjectChange(const std::string& name, const GObject& object) {
    auto itWindow = _windowObjects.findObject(name);
  	assert(_windowObjects.isValidIterator(itWindow));
  	auto &windowObj = itWindow->second;
    windowObj = object;
    transformAndClip(windowObj, _window.wo2wiMatrix());
    redraw();
  }

  void Viewport::onObjectRemoval(const std::string& name) {
    assert(_windowObjects.exists(name));
    _windowObjects.remove(name);
    redraw();
  }

  std::ostream& operator<<(std::ostream& os, const GObject& rhs){
	  for(const auto& p : rhs.coordinates())
		  os << "(" << p.x << ", " << p.y << ", " << p.y << std::endl;
	  return os;
  }

  void Viewport::transformAndClip(GObject &obj, const Transformation &t){
	  obj.transform(t);
	  bool draw = true;
	  switch(obj.type()){
	  	case GObject::Type::POINT:
	  	  draw = _clippingStrategy.clip(static_cast<GPoint&> (obj), clippingRect);
        break;
      case GObject::Type::LINE:
        draw = _clippingStrategy.clip(static_cast<GLine&> (obj), clippingRect);
        break;
      case GObject::Type::POLYGON:
        draw = _clippingStrategy.clip(static_cast<GPolygon&> (obj), clippingRect);
        break;
      case GObject::Type::BEZIER_CURVE:
      case GObject::Type::SPLINE_CURVE:
      case GObject::Type::OBJECT:
				break;
	  }
	  if(!draw)
		  obj.coordinates().clear();
  }

	void Viewport::transformAndClipAll(const Transformation &t){
		clock_t time = clock();
		{	//TODO change to a clear.() followed by an iteration over worldObjects. Test the efficiency of that.
			_windowObjects.objects() = _world->getObjects();
			for(auto &obj : _windowObjects.objects())
				transformAndClip(obj.second, t);
		}
		time = clock() - time;
		std::cout << "Took me " << time << " clock ticks ("<< ((float)time)/CLOCKS_PER_SEC << " seconds) at "
				<<  CLOCKS_PER_SEC << "Hz to transform and clip all objects" << std::endl;
	}

  Viewport::Border::Border(const ClippingRect& rect) {
    addCoordinate(Coordinate(rect.minX, rect.minY));
    addCoordinate(Coordinate(rect.minX, rect.maxY));
    addCoordinate(Coordinate(rect.maxX, rect.maxY));
    addCoordinate(Coordinate(rect.maxX, rect.minY));
    decoration.setLineColor(Color(1, 0, 0));
    decoration.setLineWidth(3.0);
  }
}
