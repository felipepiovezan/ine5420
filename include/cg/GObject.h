#ifndef CG_GOBJECT_H_
#define CG_GOBJECT_H_

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "cg/Transformations.h"
#include "cg/decorations.h"
#include "cg/exceptions.h"

namespace CG {
	class GObject;
	class Transformation;

	typedef std::shared_ptr<GObject> ObjRef;

	class Coordinate {
		public:
			Coordinate(double dx, double dy) : x(dx), y(dy), w(1) {}
			double x, y, w;

			Coordinate& operator*=(const Transformation& t);
			friend Coordinate operator+(const Coordinate &c1, const Coordinate &c2);
			friend Coordinate operator-(const Coordinate &c1, const Coordinate &c2);
	};

	class GObject {
		public:
			typedef std::vector<Coordinate> Coordinates;
			enum Type { OBJECT, POINT, LINE, POLYGON, BEZIER_CURVE, SPLINE_CURVE };

			const Coordinates& coordinates() const {return _coordinates;}
			Coordinates& coordinates() {return _coordinates;}
			int numPoints() const {return _coordinates.size();}
			Coordinate center() const;

			void transform(const Transformation& t);
			void clear() { _coordinates.clear(); }

			virtual ObjRef clone() const = 0;
			virtual Type type() const { return Type::OBJECT; }
			virtual std::string typeName() const { return "Object"; }

			Decoration decoration;

		protected:
			Coordinates _coordinates;

			void addCoordinate(int x, int y) {_coordinates.emplace_back(x,y);}
			void addCoordinate(const Coordinate& p) {_coordinates.push_back(p);}
			void addCoordinate(Coordinate&& p) {_coordinates.push_back(p);}
			void addCoordinate(const Coordinates& coords){_coordinates.insert(_coordinates.end(), coords.begin(), coords.end());}
	};

	class GPoint : public GObject {
		public:
			GPoint(int x, int y) {
				addCoordinate(x,y);
			}
			GPoint(const Coordinate& p) {
				addCoordinate(p);
			}
			GPoint(Coordinate&& p) {
				addCoordinate(p);
			}

			Type type() const { return Type::POINT; }
			std::string typeName() const { return "Point"; }

			ObjRef clone() const {
				ObjRef obj = ObjRef(new GPoint(coordinates()[0]));
				obj->decoration = decoration;
				return obj;
			}
	};

	class GLine : public GObject {
		public:
			GLine(int x1, int y1, int x2, int y2) {
				addCoordinate(x1,y1);
				addCoordinate(x2,y2);
			}
			GLine(const Coordinate& p1, const Coordinate& p2) {
				addCoordinate(p1);
				addCoordinate(p2);
			}
			GLine(Coordinate&& p1, Coordinate&& p2) {
				addCoordinate(p1);
				addCoordinate(p2);
			}

			Type type() const { return Type::LINE; }
			std::string typeName() const { return "Line"; }

			ObjRef clone() const {
				ObjRef obj = ObjRef(new GLine(coordinates()[0], coordinates()[1]));
				obj->decoration = decoration;
				return obj;
			}
	};

	class GPolygon : public GObject {
		public:
			GPolygon() {}
			GPolygon(const Coordinates& coords) {
				addCoordinate(coords);
			}
			Type type() const { return Type::POLYGON; }
			std::string typeName() const { return "Polygon"; }

			ObjRef clone() const {
				ObjRef obj = ObjRef(new GPolygon(coordinates()));
				obj->decoration = decoration;
				return obj;
			}
	};

	class BezierCurve : public GObject{
		public:
		BezierCurve(const Coordinates& coords) {
			if (coords.size() < 4) {
				throw CGException("A bezier curve must have at least 4 coordinates");
			}

			addCoordinate(coords);
		}

		Type type() const { return Type::BEZIER_CURVE; }
		std::string typeName() const { return "Bezier Curve"; }

		ObjRef clone() const {
			ObjRef obj = ObjRef(new BezierCurve(coordinates()));
			obj->decoration = decoration;
			return obj;
		}
	};

}

#endif
