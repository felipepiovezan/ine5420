#include "ui/GtkUIViewport.h"

#include <iostream>
#include <cairomm/context.h>
#include <ctime>

void GtkUIViewport::redraw() {
  queue_draw();
}

void GtkUIViewport::drawObject(const CG::GObject &obj) {
	if (!cairoCtx) return;
  if (obj.numPoints() == 0) return;

  switch (obj.type()) {
    case CG::GObject::Type::OBJECT:
      break;

    case CG::GObject::Type::POINT:
      drawPoint((const CG::GPoint&) obj);
      break;

    case CG::GObject::Type::LINE:
      drawLine((const CG::GLine&) obj);
      break;

    case CG::GObject::Type::POLYGON:
      drawPolygon((const CG::GPolygon&) obj);
      break;
    case CG::GObject::Type::_3D_OBJECT:
      draw3dObj((const CG::G3dObject&) obj);
      break;

    case CG::GObject::Type::BEZIER_CURVE:
    case CG::GObject::Type::SPLINE_CURVE:
      drawCurve((const CG::Curve&) obj);
      break;

    case CG::GObject::Type::SURFACE:
    	const CG::GSurface& surface = (CG::GSurface&) obj;
    	for(const auto& curve: surface.curves()) {
    		drawCurve(curve);
    	}
    	break;
  }
}

void GtkUIViewport::drawPoint(const CG::GPoint& point) {
  auto coord = transformCoordinate(point.coordinates()[0]);
  prepareContext(point.decoration);
  cairoCtx->move_to(coord.x, coord.y);
  cairoCtx->arc(coord.x, coord.y, 1.0, 0.0, 2.0 * M_PI);
  cairoCtx->fill_preserve();
  cairoCtx->stroke();
}

void GtkUIViewport::drawLine(const CG::GLine& line) {
  auto coords = transformCoordinates(line.coordinates());
  prepareContext(line.decoration);
  cairoCtx->move_to(coords[0].x, coords[0].y);
  cairoCtx->line_to(coords[1].x, coords[1].y);
  cairoCtx->stroke();
}

void GtkUIViewport::drawPolygon(const CG::GPolygon& polygon) {
  auto coords = transformCoordinates(polygon.coordinates());
  prepareContext(polygon.decoration);

  cairoCtx->move_to(coords[0].x, coords[0].y);
  for (unsigned int i = 0; i < coords.size(); i++) {
    cairoCtx->line_to(coords[i].x, coords[i].y);
  }
  cairoCtx->close_path();  // connect the last point with the first one

  // Fill the polygon
  cairoCtx->save();
  prepareColorContext(polygon.decoration.getFillColor());
  cairoCtx->fill_preserve();
  cairoCtx->restore();
  cairoCtx->stroke();
}

void GtkUIViewport::drawCurve(const CG::Curve& curve) {
	/*TODO: let's transform each coordinate individually instead of allocating a new vector. Let's do this in each DrawSomething() method*/
  auto coords = transformCoordinates(curve.getPath());

  if (coords.size() == 0) {
    return;
  }

  prepareContext(curve.decoration);
  cairoCtx->move_to(coords[0].x, coords[0].y);
  for (unsigned int i = 1; i < coords.size(); i++) {
    cairoCtx->line_to(coords[i].x, coords[i].y);
  }
  cairoCtx->stroke();
}

void GtkUIViewport::draw3dObj(const CG::G3dObject& obj){
	for(const auto& pol : obj.actualFaces()){
		drawPolygon(pol);
	}

}

void GtkUIViewport::prepareContext(const CG::Decoration& decoration) {
  prepareColorContext(decoration.getLineColor());
  cairoCtx->set_line_width(decoration.getLineWidth());
}

void GtkUIViewport::prepareColorContext(const CG::Color& color) {
  cairoCtx->set_source_rgba(color.r, color.g, color.b, color.a);
}

void GtkUIViewport::updateDimension() {
	_width = get_allocation().get_width();
	_height = get_allocation().get_height();
}

bool GtkUIViewport::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
  clock_t time = clock();

  cairoCtx = ctx;
  updateDimension();
  for(const auto &obj : _windowObjects.objects())
	  drawObject(*obj.second);

  drawObject(border);

  time = clock() - time;
  std::cout << "Took me " << time << " clock ticks ("<< ((float)time)/CLOCKS_PER_SEC << " seconds) at "
			<<  CLOCKS_PER_SEC << "Hz to draw all clipped objects" << std::endl;
  return true;
}
