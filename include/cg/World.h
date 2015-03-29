#ifndef CG_SCENE_H_
#define CG_SCENE_H_

#include "cg/GObject.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"

namespace CG {

  class World {
    public:
      // Object insertion
      void addObject(std::string name, const GObject& obj);
      void addObject(std::string baseName, const std::vector<GObject>& objVector);
      void createPoint(std::string name, Color color, Coordinate c);
      void createLine(std::string name, Color color, Coordinate c1, Coordinate c2);
      void createPolygon(std::string name, Color color, GObject::Coordinates coordinates);

      void removeObject(const std::string &name);

      // Object manipulation
      void translateObject(const std::string &name, double dx, double dy);
      void scaleObject(const std::string &name, double sx, double sy);
      void rotateObject(const std::string &name, double theta, const Coordinate& rotationCenter);
      void rotateObject(const std::string &name, double theta);

      const mapGObjects& getObjects() const { return _worldObjects.objects(); }

      // Events notifiers & listeners definition
      class WorldListener {
        public:
          // Called when an object is created
          virtual void onObjectCreation(const std::string& name, const GObject& object) {}

          // Called when an object is changed
          virtual void onObjectChange(const std::string& name, const GObject& object) {}

          // Called when an object is removed from the world
          virtual void onObjectRemoval(const std::string& name) {}

          virtual ~WorldListener(){}
      };
      void addListener(WorldListener& listener);

    private:
      std::vector<WorldListener*> _listeners;
      DisplayFile _worldObjects;

      void notifyObjectCreation(const std::string& name, const GObject& object) const;
      void notifyObjectChange(const std::string& name, const GObject& object) const;
      void notifyObjectRemoval(const std::string& name) const;
  };

}

#endif