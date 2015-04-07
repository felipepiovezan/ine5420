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

  prepareContext(obj.decoration);

	CG::Coordinate p = transformCoordinate(obj.coordinates()[0]);
	cairoCtx->move_to(p.x, p.y);

	if(obj.type() == CG::GObject::Type::POINT){
		cairoCtx->arc(p.x, p.y, 1.0, 0.0, 2.0 * M_PI);
		cairoCtx->fill_preserve();
		cairoCtx->stroke();
		return;
	}

	for(const auto &it : obj.coordinates()){
		CG::Coordinate q = transformCoordinate(it);
		cairoCtx->line_to(q.x, q.y);
	}

	if((obj.type() == CG::GObject::Type::POLYGON)) {
		cairoCtx->close_path();  // connect the last point with the first one

    if (obj.decoration.isFilled()) {
      CG::Color fillColor = obj.decoration.getFillColor();
      cairoCtx->save();
      cairoCtx->set_source_rgb(fillColor.r, fillColor.g, fillColor.b);
      cairoCtx->fill_preserve();
      cairoCtx->restore();
    }
  }

	cairoCtx->stroke();
}


void GtkUIViewport::prepareContext(const CG::Decoration& decoration) {
  CG::Color lineColor = decoration.getLineColor();
  cairoCtx->set_source_rgb(lineColor.r, lineColor.g, lineColor.b);
  cairoCtx->set_line_width(decoration.getLineWidth());
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
	  drawObject(obj.second);

  drawObject(border);

  time = clock() - time;
  std::cout << "Took me " << time << " clock ticks ("<< ((float)time)/CLOCKS_PER_SEC << " seconds) at "
			<<  CLOCKS_PER_SEC << "Hz to draw all clipped objects" << std::endl;
  return true;
}
