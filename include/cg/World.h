#ifndef CG_SCENE_H_
#define CG_SCENE_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"

namespace CG {

  /**
   * Represents a "world scene"
   * Each Scene instance holds its own DisplayFile, Window and Viewport,
   * providing the facade for these structures
   */
  class World {
    public:
      World();

      // Object insertion
      void addObject(std::string name, const GObject& obj);
      void addObject(std::string baseName, const std::vector<GObject>& objVector);
      void createPoint(std::string name, Color color, Coordinate c);
      void createLine(std::string name, Color color, Coordinate c1, Coordinate c2);
      void createPolygon(std::string name, Color color, GObject::Coordinates coordinates);

      // Object transformations
      void translateObject(const std::string &name, double dx, double dy);
      void scaleObject(const std::string &name, double sx, double sy);
      void rotateObject(const std::string &name, double theta, const Coordinate& rotationCenter);
      void rotateObject(const std::string &name, double theta);

      const mapGObjects& getObjects() const { return _worldObjects.objects(); }

      // Events notifiers & listeners definition
      class WorldListener {
        public:
          // Called when an object of the scene is changed
          virtual void onWorldChange(const DisplayFile&) = 0;
          virtual ~WorldListener(){}
      };
      void addListener(WorldListener& listener);

    private:
      std::vector<WorldListener*> _listeners;
      void notifyWorldChanged() const;
      DisplayFile _worldObjects;

  };

}

#endif
