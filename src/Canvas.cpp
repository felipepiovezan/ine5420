#include "Canvas.h"
#include <cairomm/context.h>

Canvas::Canvas(CG::Window *window, CG::DisplayFile *dfile) {}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  ctx->set_line_width(10.0);

  // draw red lines out from the center of the window
  ctx->set_source_rgb(0.8, 0.0, 0.0);
  ctx->move_to(0, 0);
  ctx->line_to(xc, yc);
  ctx->line_to(0, height);
  ctx->move_to(xc, yc);
  ctx->line_to(width, yc);
  ctx->stroke();

  return true;
}
