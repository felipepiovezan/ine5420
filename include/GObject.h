#ifndef CG_GOBJECT_H_
#define CG_GOBJECT_H_

#include <vector>
#include <string>
#include "Transformations.h"

/*	CONTENTS:
 *	1- Coordinate
 *	2- GObject (general class)
 *	3- GPoint
 *	4- GLine
 *	5- GPolygon
 */


namespace CG {

	class Coordinate {
		public:
			Coordinate(float x, float y) : x(x), y(y) {}

			void applyTransformation(const Transformation& t);

			float x, y, z = 1;
	};

	class GObject {
		public:
			typedef std::vector<Coordinate> Coordinates;

			int numPoints() const {return _coordinates.size();}
			const Coordinates& coordinates() const {return _coordinates;}

			void applyTransformation(const Transformation& t);
		protected:
			void addCoordinate(int x, int y) {_coordinates.emplace_back(x,y);}
			void addCoordinate(const Coordinate& p) {_coordinates.push_back(p);}
			void addCoordinate(Coordinate&& p) {_coordinates.push_back(p);}
		private:
			Coordinates _coordinates;
	};

	class GPoint : public GObject {
		public:
			GPoint(int x, int y) {addCoordinate(x,y);}
			GPoint(const Coordinate& p) {addCoordinate(p);}
			GPoint(Coordinate&& p) {addCoordinate(p);}
	};

	class GLine : public GObject {
		public:
			GLine(int x1, int y1, int x2, int y2) {addCoordinate(x1,y1); addCoordinate(x2,y2);}
			GLine(const Coordinate& p1, const Coordinate& p2) {addCoordinate(p1); addCoordinate(p2);}
			GLine(Coordinate&& p1, Coordinate&& p2) {addCoordinate(p1); addCoordinate(p2);}
	};

	class GPolygon : public GObject {
		public:
	};

}

#endif
