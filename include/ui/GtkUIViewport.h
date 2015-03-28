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
    void drawObject(const CG::GObject &obj);
    double getWidth() const { return _width; }
    double getHeight() const { return _height; }

  protected:
    double _width, _height;

    void updateDimension();
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

    Cairo::RefPtr<Cairo::Context> cairoCtx;
};

#endif
