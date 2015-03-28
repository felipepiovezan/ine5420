#ifndef CG_VIEWPORT_H_
#define CG_VIEWPORT_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/World.h"

namespace CG {

  class Viewport : public World::WorldListener {
    public:
      Viewport(Window& window) : _window(window){}

      Coordinate transformCoordinate(const Coordinate& c) const;
      GObject::Coordinates transformCoordinates(GObject::Coordinates coords) const;

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
      void onObjectChange(const std::string& name, const GObject& object);
      void onObjectRemoval(const std::string& name);

    private:
      Window _window;

    protected:
      void applyTransformation(const Transformation &t);
      virtual void redraw() = 0;
      DisplayFile _windowObjects;
  };

}

#endif
