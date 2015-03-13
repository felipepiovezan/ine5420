#include <gtkmm/drawingarea.h>
#include "Window.h"
#include "DisplayFile.h"

class Canvas : public Gtk::DrawingArea {
public:
  Canvas(CG::Window *window, CG::DisplayFile *dfile);
  ~Canvas();

protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);
  void drawObject(CG::GObject *obj, const Cairo::RefPtr<Cairo::Context>& ctx);

  CG::Window *window;
  CG::DisplayFile *displayFile;
};
