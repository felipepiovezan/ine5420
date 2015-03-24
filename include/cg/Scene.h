#ifndef CG_SCENE_H_
#define CG_SCENE_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"
#include "ui/Viewport.h" // TODO

namespace CG {

  /**
   * Represents a "world scene"
   * Each Scene instance holds its own DisplayFile, Window and Viewport,
   * providing the facade for these structures
   */
  class Scene {
    public:
      Scene();

      void createPoint(std::string name, Color color, Coordinate c);
      void createLine(std::string name, Color color, Coordinate c1, Coordinate c2);
      void createPolygon(std::string name, Color color, GObject::Coordinates coordinates);

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

    protected:
      Window window;
  		DisplayFile displayFile;
    public:
  		Viewport viewport;
  };

}

#endif
