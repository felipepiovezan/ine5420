#ifndef CG_VIEWPORT_H_
#define CG_VIEWPORT_H_

#include "cg/objects.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/World.h"
#include "cg/ClippingStrategy.h"
#include <memory>

namespace CG {

  class Viewport : public World::WorldListener {
    public:
      Viewport(Window& window, std::shared_ptr<World> world) :
        _window(window), _world(world), border(clippingRect) {}

      Coordinate transformCoordinate(const Coordinate& c) const;
      GObject::Coordinates transformCoordinates(const GObject::Coordinates& coords) const;
      double screenToWindowTransformX(double x_screen);
      double screenToWindowTransformY(double y_screen);

      virtual void redraw() = 0;
      virtual void drawObject(const GObject& obj) = 0;
      virtual double getWidth() const = 0;
      virtual double getHeight() const = 0;

      // Window manipulation
      void changeWindowZoom(double step);
      void changeWindowPosition(double sx, double sy, double sz);
      void rotateWindow(double thetaX, double thetaY, double thetaZ);
      void zoomIn()  { changeWindowZoom(-1); }
      void zoomOut() { changeWindowZoom(1); }
      void left()    { changeWindowPosition(1,0,0);}
      void right()   { changeWindowPosition(-1,0,0);}
      void up()      { changeWindowPosition(0,-1,0);}
      void down()    { changeWindowPosition(0,1,0);}
      void rotateLeft()  { rotateWindow(0,0,-15);}
      void rotateRight() { rotateWindow(0,0,+15);}
      void bendForwards()  { rotateWindow(+15,0,0);}
      void bendBackwards() { rotateWindow(-15,0,0);}
      void bendLeft()	{ rotateWindow(0,+15,0);}
      void bendRight()	{ rotateWindow(0,-15,0);}

      // World Listener methods
      void onObjectCreation(const std::string& name, ObjRef object);
      void onObjectCreation(const std::string& name, const std::vector<ObjRef> &objects);
      void onObjectChange(const std::string& name, ObjRef object);
      void onObjectRemoval(const std::string& name);

    private:
      ClippingStrategy<SimplePointClipping, NLNLineClipping, SutherlandHodgmanPolygonClipping, CurveClipping> _clippingStrategy;

    protected:
      Window _window;
      std::shared_ptr<const World> _world;
      DisplayFile _windowObjects;

      void transformAndClipAll(const Transformation &t);
      inline void transformAndClip(ObjRef, const Transformation &t);
      bool behindCamera(ObjRef obj);

      class Border : public GPolygon {
        public:
          Border(const ClippingRect& rect);
      };

      ClippingRect clippingRect = {
        .minX = -0.9,
        .maxX = 0.9,
        .minY = -0.9,
        .maxY = 0.9
      };
      Border border;
  };

}

#endif
