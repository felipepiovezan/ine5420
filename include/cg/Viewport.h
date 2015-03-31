#ifndef CG_VIEWPORT_H_
#define CG_VIEWPORT_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/World.h"
#include "cg/ClippingStrategy.h"
#include <memory>

namespace CG {

  class Viewport : public World::WorldListener {
    public:
      Viewport(Window& window, std::shared_ptr<World> world) : _window(window), _world(world){}

      Coordinate transformCoordinate(const Coordinate& c) const;
      GObject::Coordinates transformCoordinates(const GObject::Coordinates& coords) const;

      virtual void redraw() = 0;
      virtual void drawObject(const GObject& obj) = 0;
      virtual double getWidth() const = 0;
      virtual double getHeight() const = 0;

      // Window manipulation
      void changeWindowZoom(double step);
      void changeWindowPosition(double sx, double sy);
      void rotateWindow(double theta);
      void zoomIn()  { changeWindowZoom(-1); }
      void zoomOut() { changeWindowZoom(1); }
      void left()    { changeWindowPosition(1,0);}
      void right()   { changeWindowPosition(-1,0);}
      void up()      { changeWindowPosition(0,-1);}
      void down()    { changeWindowPosition(0,1);}
      void rotateLeft()  { rotateWindow(-15);}
      void rotateRight() { rotateWindow(+15);}

      // World Listener methods
      void onObjectCreation(const std::string& name, const GObject& object);
      void onObjectCreation(const std::string& name, const std::vector<GObject> &objects);
      void onObjectChange(const std::string& name, const GObject& object);
      void onObjectRemoval(const std::string& name);

    private:
      Window _window;
      std::shared_ptr<World> _world;
      ClippingStrategy<SimplePointClipping, NLNLineClipping, DoNothingPolygonClipping> _clippingStrategy;

    protected:
      void transformAndClipAll(const Transformation &t);
      inline void transformAndClip(GObject &obj, const Transformation &t);
      DisplayFile _windowObjects;
  };

}

#endif
