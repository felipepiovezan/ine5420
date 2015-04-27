#ifndef GTK_DRAWING_CONTEXT_H
#define GTK_DRAWING_CONTEXT_H

#include <gtkmm/drawingarea.h>
#include "cg/objects.h"
#include "cg/Window.h"
#include "cg/Viewport.h"


class GtkUIViewport : public CG::Viewport, public Gtk::DrawingArea {
  public:
    GtkUIViewport(CG::Window& window, std::shared_ptr<CG::World> world) : CG::Viewport(window, world) {};

    void redraw();
    void drawObject(const CG::GObject &obj);
    double getWidth() const { return _width; }
    double getHeight() const { return _height; }

    void drawPoint(const CG::GPoint& point);
    void drawLine(const CG::GLine& line);
    void drawPolygon(const CG::GPolygon& polygon);
    void drawCurve(const CG::Curve& curve);
    void draw3dObj(const CG::G3dObject& obj);

  protected:
    double _width, _height;

    void prepareContext(const CG::Decoration& decoration);
    void prepareColorContext(const CG::Color& color);
    void updateDimension();
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

    Cairo::RefPtr<Cairo::Context> cairoCtx;
};

#endif
