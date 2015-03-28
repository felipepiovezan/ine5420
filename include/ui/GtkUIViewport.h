#ifndef GTK_DRAWING_CONTEXT_H
#define GTK_DRAWING_CONTEXT_H

#include <gtkmm/drawingarea.h>
#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/Viewport.h"

class GtkUIViewport : public CG::Viewport, public Gtk::DrawingArea {
  public:
    GtkUIViewport(CG::Window& window) : CG::Viewport(window) {};

    void redraw();
    void drawPoint(CG::Coordinate p, CG::Color color);
    void drawLine(CG::Coordinate p1, CG::Coordinate p2, CG::Color color);
    void drawPolygon(CG::GObject::Coordinates cs, CG::Color color);
    double getWidth() { return width; }
    double getHeight() { return height; }

  protected:
    double width, height;

    void updateDimension();
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

    Cairo::RefPtr<Cairo::Context> cairoCtx;
};

#endif
