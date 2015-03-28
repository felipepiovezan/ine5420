#include "ui/GtkUIViewport.h"

#include <cairomm/context.h>

void GtkUIViewport::redraw() {
  queue_draw();
}

void GtkUIViewport::drawPoint(CG::Coordinate p, CG::Color color) {
  if (!cairoCtx) return;

  cairoCtx->set_source_rgb(color.r, color.g, color.b);
  cairoCtx->move_to(p.x, p.y);
  cairoCtx->arc(p.x, p.y, 1.0, 0.0, 2.0 * M_PI);
  cairoCtx->fill_preserve();
  cairoCtx->stroke();
}

void GtkUIViewport::drawLine(CG::Coordinate p1, CG::Coordinate p2, CG::Color color) {
  if (!cairoCtx) return;

  cairoCtx->set_source_rgb(color.r, color.g, color.b);
  cairoCtx->move_to(p1.x, p1.y);
  cairoCtx->line_to(p2.x, p2.y);
  cairoCtx->stroke();
}

void GtkUIViewport::drawPolygon(CG::GObject::Coordinates cs, CG::Color color) {
  if (!cairoCtx) return;

  cairoCtx->set_source_rgb(color.r, color.g, color.b);
  cairoCtx->move_to(cs[0].x, cs[0].y);

  for(const auto &it : cs) {
    cairoCtx->line_to(it.x, it.y);
  }

  // connect the last point with the first one
  cairoCtx->line_to(cs[0].x, cs[0].y);
  cairoCtx->stroke();
}

void GtkUIViewport::updateDimension() {
  width = get_allocation().get_width();
  height = get_allocation().get_height();
}

bool GtkUIViewport::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
  cairoCtx = ctx;
  updateDimension();
  return true;
}
