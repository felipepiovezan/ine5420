#ifndef CG_VIEWPORT_H_
#define CG_VIEWPORT_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/DrawingContext.h"
#include <cassert>

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

      //methods called by the gui, transformations on objects
      // TODO: remove it!
      const DisplayFile* getDisplayFile(){ return displayFile;}
  		void applyTranslation(const std::string &name, double dx, double dy);
  		void applyScaling(const std::string &name, double sx, double xy);
  		void applyRotation(const std::string &name, double theta, const CG::Coordinate& rotationCenter);

    protected:
      DrawingContext* ctx;
      Window* window;
      DisplayFile* displayFile;
  };

}

#endif
