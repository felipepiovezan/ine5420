#include <gtkmm/drawingarea.h>
#include "Window.h"
#include "DisplayFile.h"
#include "Coordinate.h"

class Canvas : public Gtk::DrawingArea {
public:
  Canvas(CG::Window *window, CG::DisplayFile *dfile);
  ~Canvas();

protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

  void drawObject(CG::GObject *obj, const Cairo::RefPtr<Cairo::Context>& ctx);
  int transformX(int x);
  int transformY(int y);

  CG::Window *window;
  CG::DisplayFile *displayFile;
};
