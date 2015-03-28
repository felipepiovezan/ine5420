#ifndef CG_VIEWPORT_H_
#define CG_VIEWPORT_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/DrawingContext.h"
#include "cg/World.h"

namespace CG {

  class Viewport : public World::WorldListener {
    public:
      Viewport(Window& window) : _window(window){}

      //TODO: this method must be moved to the GUI class: void drawObject(const GObject& obj);
      //TODO: this method must be moved to the GUI class: Coordinate transformCoordinate(const Coordinate& c) const;
      //TODO: this method must be moved to the GUI class: GObject::Coordinates transformCoordinates(GObject::Coordinates coords) const;

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
      void applyTransformation(const Transformation &t);

      //World Listener methods
      void onWorldChange(const DisplayFile& worldObjects);

      //Event notifier and listeners

      class ViewportListener {
              public:
                // Called when an object of the scene is changed
                virtual void onViewportChange(const DisplayFile&) = 0;
                virtual ~ViewportListener(){}
      };
      void addListener(ViewportListener& listener);


    private:
      Window _window;
      DisplayFile _windowObjects;
      std::vector<ViewportListener*> _listeners;
      void notifyViewportChanged();

  };

}

#endif
