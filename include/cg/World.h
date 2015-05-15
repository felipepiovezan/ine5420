#ifndef CG_SCENE_H_
#define CG_SCENE_H_

#include "cg/decorations.h"
#include "cg/objects.h"
#include "cg/Window.h"
#include "cg/DisplayFile.h"

namespace CG {

  class World {
    public:
      // Object insertion
      void addObject(std::string name, ObjRef obj);
      void addObject(std::string baseName, const std::vector<ObjRef>& objVector);
      void createPoint(std::string name, Decoration decoration, Coordinate c);
      void createLine(std::string name, Decoration decoration, Coordinate c1, Coordinate c2);
      void createPolygon(std::string name, Decoration decoration, GObject::Coordinates coordinates);
      void createBezierCurve(std::string name, Decoration decoration, GObject::Coordinates coordinates);
      void createSplineCurve(std::string name, Decoration decoration, GObject::Coordinates coordinates);
      void createBezierSurface(std::string name, Decoration decoration, GObject::Coordinates coordinates);
      void createSplineSurface(std::string name, Decoration decoration, GObject::Coordinates coordinates);

      void removeObject(const std::string &name);

      // Object manipulation
      void translateObject(const std::string &name, double dx, double dy, double dz);
      void scaleObject(const std::string &name, double sx, double sy, double sz);
      void rotateObject(const std::string &name, double thetaX, double thetaY, double thetaZ, const Coordinate& rotationCenter);
      void rotateObject(const std::string &name, double thetaX, double thetaY, double thetaZ);

      const mapGObjects& getObjects() const { return _worldObjects.objects(); }

      // Events notifiers & listeners definition
      class WorldListener {
        public:
          // Called when an object is created
          virtual void onObjectCreation(const std::string& name, ObjRef object) {}

          // Called when a collection of objects is created
          virtual void onObjectCreation(const std::string& name, const std::vector<ObjRef>& objects) {}

          // Called when an object is changed
          virtual void onObjectChange(const std::string& name, ObjRef object) {}

          // Called when an object is removed from the world
          virtual void onObjectRemoval(const std::string& name) {}

          virtual ~WorldListener(){}
      };
      void addListener(WorldListener& listener);

    private:
      std::vector<WorldListener*> _listeners;
      DisplayFile _worldObjects;

      void notifyObjectCreation(const std::string& name, ObjRef object) const;
      void notifyObjectCreation(const std::string& name, const std::vector<ObjRef>& objects) const;
      void notifyObjectChange(const std::string& name, ObjRef object) const;
      void notifyObjectRemoval(const std::string& name) const;
  };

}

#endif
