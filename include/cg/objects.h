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
		friend class ObjReader;
		template <typename PointStrategy, typename LineStrategy, typename PolygonStrategy, typename CurveStrategy>
		friend class ClippingStrategy;
		public:
			typedef std::vector<Coordinate> Coordinates;
			enum Type { OBJECT, POINT, LINE, POLYGON, BEZIER_CURVE, SPLINE_CURVE, _3D_OBJECT, SURFACE};

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

			virtual void applyPerspective(double dop);

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

		ObjRef clone() const & {return ObjRef(new Curve(*this));}
		ObjRef clone() && {return ObjRef(new Curve(std::move(*this)));}
		/**
		 * Must regenerate the parametric curve with t varying between 0 and 1 with defined step (for each sub-curve)
		 */
		virtual void regeneratePath(double step) {std::cerr << "THIS METHOD SHOULD NEVER BE CALLED" << std::endl;};


	 public:
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
		friend class ObjReader;
		template <typename PointStrategy, typename LineStrategy, typename PolygonStrategy, typename CurveStrategy>
		friend class ClippingStrategy;
	public:
		typedef std::vector<std::vector<int>> FaceList;

		G3dObject() = default;
		G3dObject(const Coordinates& coords, const FaceList edgeList) : GObject(coords), _faceList(edgeList){}

		Type type() const { return Type::_3D_OBJECT; }
		std::string typeName() const { return "3D Object"; }

		ObjRef clone() const & {return ObjRef(new G3dObject(*this));}
		ObjRef clone() && {return ObjRef(new G3dObject(std::move(*this)));}

		const FaceList& faceList() const {return _faceList;}
		FaceList& faceList() {return _faceList;}
		const std::vector<CG::GPolygon>& actualFaces() const { return _actualFaces;}
	private:
		FaceList _faceList;
		std::vector<CG::GPolygon> _actualFaces;
	};


	/*The GSurface implementation is largely based on the implementation suggested by the professor:
	 * https://gist.github.com/awangenh/73983b81541abf2c71cc#file-forwarddiff_foley_vandam-pde-L66
	 * */
	class GSurface : public GObject{
	public:
		enum SurfaceType{BEZIER, B_SPLINE};

		GSurface(SurfaceType type, const Coordinates& coords);
		void regeneratePath( int ns, int nt);
		std::vector<Curve>& curves(){return _curves;}
		const std::vector<Curve>& curves() const {return _curves;}

		Type type() const { return Type::SURFACE; }
		std::string typeName() const { return "Surface"; }

		ObjRef clone() const & {return ObjRef(new GSurface(*this));}
		ObjRef clone() && {return ObjRef(new GSurface(std::move(*this)));}

	private:
		std::vector<Curve> _curves;

		const double (&_geometry_matrix)[4][4];
		std::array<std::array<double, 4>, 4> _coords_x;
		std::array<std::array<double, 4>, 4> _coords_y;
		std::array<std::array<double, 4>, 4> _coords_z;
		std::array<std::array<double, 4>, 4> _cx;
		std::array<std::array<double, 4>, 4> _cy;
		std::array<std::array<double, 4>, 4> _cz;
		std::array<std::array<double, 4>, 4> _et;
		std::array<std::array<double, 4>, 4> _es;
		std::array<std::array<double, 4>, 4> _DDx;
		std::array<std::array<double, 4>, 4> _DDy;
		std::array<std::array<double, 4>, 4> _DDz;
		/* Constants for each surface type*/
		constexpr static double bezier_matrix[4][4] =  { {-1,  3, -3,  1},
														{ 3, -6,  3,  0},
														{-3,  3,  0,  0},
														{ 1,  0,  0,  0} };
		constexpr static double spline_matrix[4][4] =  { {-1/6.0,  0.5, -0.5,  1/6.0},
														{ 0.5, -1,  0.5,  0},
														{-0.5,  0,  0.5,  0},
														{ 1/6.0,  4/6.0,  1/6.0,  0} };
		/*Methods used by the Draw Surface function*/
		void updateCoords();
		void calculateCoefficients();
		void createDeltaMatrices(double delta_s, double delta_t);
		void createForwardDiffMatrices();
		void UpdateForwardDiffMatrices();
		void makeCurve( int n,
			                      double x, double Dx, double D2x, double D3x,
			                      double y, double Dy, double D2y, double D3y,
			                      double z, double Dz, double D2z, double D3z);

	};

}

#endif
