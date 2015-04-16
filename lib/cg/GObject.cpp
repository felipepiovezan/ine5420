#include "cg/GObject.h"

namespace CG {
	Coordinate& Coordinate::operator*=(const Transformation& rhs){
		const auto &m = rhs.m();
		double x = this->x, y = this->y, w = this->w;
		this->x = x*m[0][0] + y*m[1][0] + w*m[2][0];
		this->y = x*m[0][1] + y*m[1][1] + w*m[2][1];
		this->w = x*m[0][2] + y*m[1][2] + w*m[2][2];
		return *this;
	}

	Coordinate operator*(Coordinate lhs, const Transformation& rhs){
		lhs *= rhs;
		return lhs;
	}

	Coordinate operator+(const Coordinate &c1, const Coordinate &c2) {
		return Coordinate(c1.x + c2.x, c1.y + c2.y);
	}

	Coordinate operator-(const Coordinate &c1, const Coordinate &c2) {
		return Coordinate(c1.x - c2.x, c1.y - c2.y);
	}

	Coordinate GObject::center() const {
		Coordinate r(0, 0);
		int n = numPoints();

		for(auto &p : _coordinates){
			r.x += p.x;
			r.y += p.y;
		}

		r.x /= n;
		r.y /= n;
		return r;
	}

	void GObject::transform(const Transformation& t){
		for(auto &p : _coordinates){
			p*=(t);
		}
	}

	BezierCurve::BezierCurve(const Coordinates& coords) {
		if (coords.size() < 4 || (coords.size() - 4) % 3 != 0) {
			throw CGException("A bezier curve must be defined with 4, 7, 10, 13, 16, ... coordinates");
		}

		addCoordinate(coords);
		regeneratePath(0.1);
	}

	/**
	 * Blending function to calculate the path of the bezier curve
	 * t must be between 0 and 1
	 */
	Coordinate BezierCurve::calc(double t) const {
		double t2 = t * t;     // t square
		double t3 = t2 * t; 	 // t cube
		double ti = 1 - t;     // t inverse
		double ti2 = ti * ti;  // ti square
		double ti3 = ti2 * ti; // ti cube
		auto coords = coordinates();

		double x = ti3 * coords[0].x + 3 * ti2 * t * coords[1].x + 3 * ti * t2 * coords[2].x + t3 * coords[3].x;
		double y = ti3 * coords[0].y + 3 * ti2 * t * coords[1].y + 3 * ti * t2 * coords[2].y + t3 * coords[3].y;
		//double z = ti3 * coords[0].z + 3 * ti2 * t * coords[1].z + 3 * ti * t2 * coords[2].z + t3 * coords[3].z;
		return Coordinate(x, y);
	}

	/**
	 * Recalculate the generated coordinates of the curve with specified step (0 to 1)
	 */
	void BezierCurve::regeneratePath(double step) {
		// TODO: consider multiple curves
		path.clear();
	  for (double t = 0; t < 1; t += step) {
	    Coordinate c = this->calc(t);
	    path.push_back(c);
	  }
		path.push_back(coordinates()[3]); // Make sure the last point is included
	}

}
