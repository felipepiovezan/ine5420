#include "Viewport.h"
#include <cairomm/context.h>
#include <map>

Viewport::Viewport(CG::Window* window, CG::DisplayFile* dfile)
  : _window(window), _displayFile(dfile) {}

bool Viewport::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
	for(const auto &it : _displayFile->objects()){
		drawObject(it.second, ctx);
	}
	return true;
}

void Viewport::drawObject(const CG::GObject &obj, const Cairo::RefPtr<Cairo::Context>& ctx) {
  if (obj.numPoints() == 0)
    return;

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
int Viewport::transformX(int x) {
	Gtk::Allocation allocation = get_allocation();
	int width = allocation.get_height();
	return width * (x - _window->xmin()) / (_window->xmax() - _window->xmin());
}

int Viewport::transformY(int y) {
  Gtk::Allocation allocation = get_allocation();
  const int height = allocation.get_height();
  return height * (1 - ((y - _window->ymin()) / (_window->ymax() - _window->ymin())));
}
