#ifndef CG_SCENE_H_
#define CG_SCENE_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "cg/DrawingContext.h"
#include "cg/Viewport.h"

namespace CG {

  /**
   * Represents a "world scene"
   * Each Scene instance holds its own DisplayFile, Window and Viewport,
   * providing the facade for these structures
   */
  class Scene {
    protected:
      Window window;
    	DisplayFile displayFile;
      Viewport viewport;

    public:
      Scene(DrawingContext& ctx);

      // Object creation
      void createPoint(std::string name, Color color, Coordinate c);
      void createLine(std::string name, Color color, Coordinate c1, Coordinate c2);
      void createPolygon(std::string name, Color color, GObject::Coordinates coordinates);

      // Object manipulation
      void translateObject(const std::string &name, double dx, double dy);
  		void scaleObject(const std::string &name, double sx, double sy);
  		void rotateObject(const std::string &name, double theta, const Coordinate& rotationCenter);

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

      // Events notifiers & listeners definition
      class Listener {
        public:
          // Called when an object of the scene is changed
          virtual void onObjectChange(DisplayFile* displayFile) {}

          // Called when the window is changed
          virtual void onWindowChange(Window* window) {}
      };
      void addListener(Listener* listener);

    private:
      std::vector<Listener*> listeners;
      void notifyWindowChange();
      void notifyObjectChange();
  };

}

#endif
