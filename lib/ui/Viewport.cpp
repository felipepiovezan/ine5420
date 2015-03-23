#include "ui/Viewport.h"

#include <cairomm/context.h>
#include <map>

Viewport::Viewport(CG::Window* window, CG::DisplayFile* dfile)
  : _window(window), _displayFile(dfile) {}

bool Viewport::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	for(const auto &it : _displayFile->windowObjects()){
		drawObject(it.second, ctx);
	}
	return true;
}

void Viewport::drawObject(const CG::GObject &obj, const Cairo::RefPtr<Cairo::Context>& ctx) {
  if (obj.numPoints() == 0)
    return;

  ctx->set_source_rgb(obj.color.r, obj.color.g, obj.color.b);

  const CG::GObject::Coordinates& coordinates = obj.coordinates();
  const CG::Coordinate& firstCoord = coordinates[0];

  ctx->move_to(transformX(firstCoord.x), transformY(firstCoord.y));

  if (obj.numPoints() == 1) {
    ctx->arc(transformX(firstCoord.x), transformY(firstCoord.y), 1.0, 0.0, 2.0 * M_PI);
    ctx->fill_preserve();
    ctx->stroke();
    return;
  }

  for(const auto &it : coordinates) {
    ctx->line_to(transformX(it.x), transformY(it.y));
  }

  // If object is a polygon, connect the last point with the first one
  if (obj.numPoints() > 2)
    ctx->line_to(transformX(firstCoord.x), transformY(firstCoord.y));

  ctx->stroke();
}


//Transforms the coordinates of the World into a coordinate of the visible area.
double Viewport::transformX(double x) {
	Gtk::Allocation allocation = get_allocation();
	int width = allocation.get_height();
	return width * (x - _window->xmin()) / (_window->xmax() - _window->xmin());
}

double Viewport::transformY(double y) {
  Gtk::Allocation allocation = get_allocation();
  const int height = allocation.get_height();
  return height * (1 - ((y - _window->ymin()) / (_window->ymax() - _window->ymin())));
}

void Viewport::applyTranslation(const std::string &name, double dx, double dy){
	auto itWindow = _displayFile->findWindowObject(name);
	auto itWorld = _displayFile->findWorldObject(name);
	assert(_displayFile->isValidWindowIterator(itWindow) && _displayFile->isValidWorldIterator(itWorld));

	auto &worldObject = itWorld->second;
	auto &windowObject = itWindow->second;

    CG::Transformation transformation = CG::Transformation::newTranslation(dx, dy);
    worldObject.transform(transformation);
    //TODO: transform these two lines into a single operator * line
    windowObject = worldObject;
    windowObject.transform(_window->wo2wiMatrix());
}

void Viewport::applyScaling(const std::string &name, double sx, double sy){
	auto itWindow = _displayFile->findWindowObject(name);
	auto itWorld = _displayFile->findWorldObject(name);
	assert(_displayFile->isValidWindowIterator(itWindow) && _displayFile->isValidWorldIterator(itWorld));

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
    windowObject.transform(_window->wo2wiMatrix());
}

void Viewport::applyRotation(const std::string &name, double theta, const CG::Coordinate &rotationCenter){
	auto itWindow = _displayFile->findWindowObject(name);
	auto itWorld = _displayFile->findWorldObject(name);
	assert(_displayFile->isValidWindowIterator(itWindow) && _displayFile->isValidWorldIterator(itWorld));

	auto &worldObject = itWorld->second;
	auto &windowObject = itWindow->second;

	CG::Transformation transformation = CG::Transformation::newRotationAroundPoint(CG::Transformation::toRadians(theta), rotationCenter);

    worldObject.transform(transformation);
    //TODO: transform these two lines into a single operator * line
    windowObject = worldObject;
    windowObject.transform(_window->wo2wiMatrix());
}

void Viewport::changeWindowZoom(double step){
	_window->zoom(step);
	_window->updateMatrix();
	_displayFile->updateWindowCoords(_window->wo2wiMatrix());
	redraw();
}

void Viewport::changeWindowPosition(double sx, double sy){
	_window->moveCenter(sx, sy);
	_window->updateMatrix();
	_displayFile->updateWindowCoords(_window->wo2wiMatrix());
	redraw();
}
