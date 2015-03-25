#include "cg/Scene.h"

#include "cg/Transformations.h"

namespace CG {

  Scene::Scene(DrawingContext& ctx) :
    window(0, 0, 10, 10, 0),
    displayFile(),
    viewport(&ctx, &window, &displayFile)
  {
    viewport.redraw();
  }

  void Scene::createPoint(std::string name, Color color, Coordinate c) {
    GPoint point(c);
    point.color = color;
    displayFile.add(name, point, window.wo2wiMatrix());
    viewport.redraw();
  }

  void Scene::createLine(std::string name, Color color, Coordinate c1, Coordinate c2) {
    GLine line(c1, c2);
    line.color = color;
    displayFile.add(name, line, window.wo2wiMatrix());
    viewport.redraw();
  }

  void Scene::createPolygon(std::string name, Color color, GObject::Coordinates coordinates) {
    GPolygon polygon(coordinates);
    polygon.color = color;
    displayFile.add(name, polygon, window.wo2wiMatrix());
    viewport.redraw();
  }

  void Scene::changeWindowZoom(double step){
  	window.zoom(step);
  	window.updateMatrix();
  	displayFile.updateWindowCoords(window.wo2wiMatrix());
    viewport.redraw();
  }

  void Scene::changeWindowPosition(double sx, double sy){
  	window.move(sx, sy);
  	window.updateMatrix();
  	displayFile.updateWindowCoords(window.wo2wiMatrix());
    viewport.redraw();
  }

  void Scene::rotateWindow(double theta){
  	window.rotate(Transformation::toRadians(theta));
  	window.updateMatrix();
  	displayFile.updateWindowCoords(window.wo2wiMatrix());
    viewport.redraw();
  }
}
