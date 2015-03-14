#include "Canvas.h"
#include <cairomm/context.h>
#include <map>
#include <iostream>

Canvas::Canvas(CG::Window *window, CG::DisplayFile *dfile)
  : window(window), displayFile(dfile) {}

Canvas::~Canvas() {
  delete window;
  delete displayFile;
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& ctx) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // coordinates for the center of the window
  int xc, yc;
  xc = width / 2;
  yc = height / 2;

  ctx->set_line_width(0.5);

  // Drawing x axis TODO: send axis to real world
  ctx->set_source_rgb(1, 0, 0);
  ctx->move_to(0, yc);
  ctx->line_to(width, yc);
  ctx->stroke();

  // Drawing y axis TODO: send axis to real world
  ctx->set_source_rgb(0, 1, 0);
  ctx->move_to(xc, 0);
  ctx->line_to(xc, height);
  ctx->stroke();

  ctx->set_source_rgb(0, 0, 0);
  ctx->set_line_width(5);

  for(CG::DisplayFile::Iterator it = displayFile->begin(); it != displayFile->end(); it++) {
    drawObject(it->second, ctx);
  }

  return true;
}

void Canvas::drawObject(CG::GObject *obj, const Cairo::RefPtr<Cairo::Context>& ctx) {
  if (obj->begin() == obj->end())
    return;

  // TODO: viewport transform
  // TODO: Point not visible

  CG::GObject::CoordinateIterator it = obj->begin();
  ctx->move_to(transformX(it->x), transformY(it->y));

  for(it = obj->begin(); it != obj->end(); it++) {
    ctx->line_to(transformX(it->x), transformY(it->y));
  }

  ctx->stroke();
}

int Canvas::transformX(int x) {
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  return width * (x - window->xmin) / (window->xmax - window->xmin);
}

int Canvas::transformY(int y) {
  Gtk::Allocation allocation = get_allocation();
  const int height = allocation.get_height();
  return height * (1 - ((y - window->ymin) / (window->ymax - window->ymin)));
}
