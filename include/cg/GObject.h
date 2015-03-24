#ifndef CG_GOBJECT_H_
#define CG_GOBJECT_H_

#include <vector>
#include <string>
#include <map>
#include "cg/Transformations.h"

/*	CONTENTS:
 *	0- Coordinate
 *	1- Color
 *	2- GObject (general class)
 *	3- GPoint
 *	4- GLine
 *	5- GPolygon
 */

namespace CG {
	class Transformation;
	class Coordinate {
		public:
			Coordinate(double dx, double dy) : x(dx), y(dy) {}
			Coordinate& operator*=(const Transformation& t);
			double x, y, z = 1;

			friend Coordinate operator+(const Coordinate &c1, const Coordinate &c2);
			friend Coordinate operator-(const Coordinate &c1, const Coordinate &c2);
	};

	class Color {
		public:
			Color() : r(0), g(0), b(0) {}
			Color(double r, double g, double b) : r(r), g(g), b(b) {}
			double r, g, b;
	};

	class GObject {
		public:
			typedef std::vector<Coordinate> Coordinates;

			//TODO: change this.
			enum Type { OBJECT, POINT, LINE, POLYGON };
			static const std::string TypeNames[];

			GObject(Type type = OBJECT) : _type(type) {};
			Type type() const { return _type; }

			const Coordinates& coordinates() const {return _coordinates;}
			int numPoints() const {return _coordinates.size();}
			Coordinate center() const;

			void transform(const Transformation& t);

			Color color;

		protected:
			Type _type;

			void addCoordinate(int x, int y) {_coordinates.emplace_back(x,y);}
			void addCoordinate(const Coordinate& p) {_coordinates.push_back(p);}
			void addCoordinate(Coordinate&& p) {_coordinates.push_back(p);}
			void addCoordinate(const Coordinates& coords){_coordinates.insert(_coordinates.end(), coords.begin(), coords.end());}
		private:
			Coordinates _coordinates;
	};

	class GPoint : public GObject {
		public:
			GPoint(int x, int y) : GObject(POINT) {addCoordinate(x,y);}
			GPoint(const Coordinate& p) : GObject(POINT) {addCoordinate(p);}
			GPoint(Coordinate&& p) : GObject(POINT) {addCoordinate(p);}
	};

	class GLine : public GObject {
		public:
			GLine(int x1, int y1, int x2, int y2) : GObject(LINE) {addCoordinate(x1,y1); addCoordinate(x2,y2);}
			GLine(const Coordinate& p1, const Coordinate& p2) : GObject(LINE) {addCoordinate(p1); addCoordinate(p2);}
			GLine(Coordinate&& p1, Coordinate&& p2) : GObject(LINE) {addCoordinate(p1); addCoordinate(p2);}
	};

	class GPolygon : public GObject {
		public:
			GPolygon(const Coordinates& coords) : GObject(POLYGON) {addCoordinate(coords);}
	};

}

#endif
