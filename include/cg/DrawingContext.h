#ifndef CG_DRAWING_CONTEXT_H_
#define CG_DRAWING_CONTEXT_H_

#include <vector>
#include "cg/GObject.h"

namespace CG {

  /**
   * A concrete subclass of Drawing Context must be implemented and provided
   * to the Viewport. Consider all coordinates already transformed to the viewport
   * standard (origin in the top-left corner)
   */
  class DrawingContext {
    public:
      virtual void redraw() = 0;
      virtual void drawPoint(Coordinate p, Color color) = 0;
      virtual void drawLine(Coordinate p1, Coordinate p2, Color color) = 0;
      virtual void drawPolygon(GObject::Coordinates cs, Color color) = 0;
      virtual double getWidth() = 0;
      virtual double getHeight() = 0;

      class Listener {
        public:
          virtual void onContextChange() = 0;
      };

      void addListener(Listener* listener) { listeners.push_back(listener); }
      void notifyContextChange() {
        for(auto &it : listeners) {
          it->onContextChange();
        }
      }

    private:
      std::vector<Listener*> listeners;
  };

}

#endif
