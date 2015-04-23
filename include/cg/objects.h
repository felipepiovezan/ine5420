#ifndef CG_OBJECTS_H_
#define CG_OBJECTS_H_

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include "cg/Transformations.h"
#include "cg/decorations.h"
#include "cg/exceptions.h"

namespace CG {
	class GObject;
	class Transformation;

	typedef std::shared_ptr<GObject> ObjRef;

	class Coordinate {
		public:
			Coordinate() : x(0), y(0), z(0), w(1) {}
			Coordinate(double dx, double dy, double dz = 0) : x(dx), y(dy), z(dz), w(1) {}
			double x, y, z, w;

			Coordinate& operator*=(const Transformation& t);
			friend Coordinate operator+(const Coordinate &c1, const Coordinate &c2);
			friend Coordinate operator-(const Coordinate &c1, const Coordinate &c2);
	};

	class GObject {
		public:
			typedef std::vector<Coordinate> Coordinates;
			enum Type { OBJECT, POINT, LINE, POLYGON, BEZIER_CURVE, SPLINE_CURVE, _3D_OBJECT};

			const Coordinates& coordinates() const {return _coordinates;}
			Coordinates& coordinates() {return _coordinates;}
			int numPoints() const {return _coordinates.size();}
			Coordinate center() const;

			void transform(const Transformation& t);
			void clear() { _coordinates.clear(); }

			virtual ObjRef clone() const & = 0;
			virtual ObjRef clone() && = 0;

			virtual Type type() const { return Type::OBJECT; }
			virtual std::string typeName() const { return "Object"; }

			Decoration decoration;

			virtual ~GObject(){}

		protected:
			Coordinates _coordinates;

			GObject(){}
			GObject(const Coordinates& coords) : _coordinates(coords){}

			void addCoordinate(double x, double y, double z) {_coordinates.emplace_back(x,y,z);}
			void addCoordinate(const Coordinate& p) {_coordinates.push_back(p);}
			void addCoordinate(Coordinate&& p) {_coordinates.push_back(p);}
			void addCoordinate(const Coordinates& coords){_coordinates.insert(_coordinates.end(), coords.begin(), coords.end());}
	};

	class GPoint : public GObject {
		public:
			GPoint(double x, double y, double z) {
				addCoordinate(x,y,z);
			}
			GPoint(const Coordinate& p) {
				addCoordinate(p);
			}
			GPoint(Coordinate&& p) {
				addCoordinate(p);
			}

			Type type() const { return Type::POINT; }
			std::string typeName() const { return "Point"; }

			ObjRef clone() const & {return ObjRef(new GPoint(*this));}
			ObjRef clone() && {return ObjRef(new GPoint(std::move(*this)));}
	};

	class GLine : public GObject {
		public:
			GLine(double x1, double y1, double x2, double y2, double z1, double z2) {
				addCoordinate(x1,y1,z1);
				addCoordinate(x2,y2,z2);
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

			ObjRef clone() const & {return ObjRef(new GLine(*this));}
			ObjRef clone() && {return ObjRef(new GLine(std::move(*this)));}
	};

	class GPolygon : public GObject {
		public:
			GPolygon() {}
			GPolygon(const Coordinates& coords) {
				addCoordinate(coords);
			}
			Type type() const { return Type::POLYGON; }
			std::string typeName() const { return "Polygon"; }

			ObjRef clone() const & {return ObjRef(new GPolygon(*this));}
			ObjRef clone() && {return ObjRef(new GPolygon(std::move(*this)));}
	};

	class Curve : public GObject {
	 public:
		const GObject::Coordinates& getPath() const { return path; }
		void setPath(GObject::Coordinates& newPath) { path = newPath; }

		/**
		 * Must regenerate the parametric curve with t varying between 0 and 1 with defined step (for each sub-curve)
		 */
		virtual void regeneratePath(double step) = 0;

	 protected:
	 	GObject::Coordinates path; // Holds generated coordinates of curve with specified precision
	};

	class BezierCurve : public Curve {
	 public:
		BezierCurve(const Coordinates& coords);

		Type type() const { return Type::BEZIER_CURVE; }
		std::string typeName() const { return "Bezier Curve"; }

		ObjRef clone() const & {return ObjRef(new BezierCurve(*this));}
		ObjRef clone() && {return ObjRef(new BezierCurve(std::move(*this)));}

		void regeneratePath(double step);
	};

	class SplineCurve : public Curve {
	 public:
		SplineCurve(const Coordinates& coords);

		Type type() const { return Type::SPLINE_CURVE; }
		std::string typeName() const { return "Spline Curve"; }

		ObjRef clone() const & {return ObjRef(new SplineCurve(*this));}
		ObjRef clone() && {return ObjRef(new SplineCurve(std::move(*this)));}

		void regeneratePath(double step);

		void coefficients(double, double, double, double, double&, double&, double&, double&);
		void differences(double, double, double, double, double, double, double, double&, double&, double&);
	};

	class G3dObject : public GObject{
	public:
		typedef std::vector<std::pair<int, int>> EdgeList;

		G3dObject(const Coordinates& coords, const EdgeList edgeList) : GObject(coords), _edgeList(edgeList){}

		ObjRef clone() const & {return ObjRef(new G3dObject(*this));}
		ObjRef clone() && {return ObjRef(new G3dObject(std::move(*this)));}

		const EdgeList& edgeList() const {return _edgeList;}
		EdgeList& edgeList() {return _edgeList;}
	private:
		EdgeList _edgeList;
	};

}

#endif
