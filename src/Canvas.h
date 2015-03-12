#include <gtkmm/drawingarea.h>

class Canvas : public Gtk::DrawingArea {
public:

protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
};
