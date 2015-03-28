#include "ui/GtkUIViewport.h"
#include <iostream>
#include <cairomm/context.h>

void GtkUIViewport::redraw() {
  queue_draw();
}

void GtkUIViewport::drawObject(const CG::GObject &obj) {
	if (!cairoCtx) return;
	cairoCtx->set_source_rgb(obj.color.r, obj.color.g, obj.color.b);

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

	if((obj.type() == CG::GObject::Type::POLYGON))
		cairoCtx->line_to(p.x, p.y);

	cairoCtx->stroke();
}

void GtkUIViewport::updateDimension() {
	_width = get_allocation().get_width();
	_height = get_allocation().get_height();
}

bool GtkUIViewport::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
  cairoCtx = ctx;
  updateDimension();
  for(const auto &obj : _windowObjects.objects())
	  drawObject(obj.second);
  return true;
}
