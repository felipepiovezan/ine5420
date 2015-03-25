#ifndef CG_VIEWPORT_H_
#define CG_VIEWPORT_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/DrawingContext.h"

namespace CG {

  class Viewport : public DrawingContext::Listener {
    public:
      Viewport(DrawingContext *ctx, Window* window, DisplayFile* dfile) :
        ctx(ctx), window(window), displayFile(dfile) {
          ctx->addListener(this);
        }

      void drawObject(const GObject& obj);
      Coordinate transformCoordinate(const Coordinate& c) const;
      GObject::Coordinates transformCoordinates(GObject::Coordinates coords) const;

      void redraw() { ctx->redraw(); }
      // DrawingContext::Listener implementation
      void onContextChange();

    protected:
      DrawingContext* ctx;
      Window* window;
      DisplayFile* displayFile;
  };

}

#endif
