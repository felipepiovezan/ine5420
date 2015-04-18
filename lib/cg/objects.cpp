#include "cg/objects.h"

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
	 * initCoord indicates the index of the coordinate to take as initial point of current cubic curve interaction
	 */
	Coordinate BezierCurve::calc(double t, int initCoord = 0) const {
		double t2 = t * t;     // t square
		double t3 = t2 * t; 	 // t cube
		double ti = 1 - t;     // t inverse
		double ti2 = ti * ti;  // ti square
		double ti3 = ti2 * ti; // ti cube
		auto coords = coordinates();

		double x = ti3 * coords[initCoord].x + 3 * ti2 * t * coords[initCoord + 1].x + 3 * ti * t2 * coords[initCoord + 2].x + t3 * coords[initCoord + 3].x;
		double y = ti3 * coords[initCoord].y + 3 * ti2 * t * coords[initCoord + 1].y + 3 * ti * t2 * coords[initCoord + 2].y + t3 * coords[initCoord + 3].y;
		return Coordinate(x, y);
	}

	/**
	 * Recalculate the generated coordinates of the curve with specified step (0 to 1)
	 */
	void BezierCurve::regeneratePath(double step) {
		// The number of cubic curves to generate (4 points make 1 curve, 7 points make 2 curves etc)
		int curves = ((coordinates().size() - 4) / 3) + 1;

		path.clear();
		for (int i = 0; i < curves; i++) {
	  	for (double t = 0; t < 1; t += step) {
	    	Coordinate c = this->calc(t, i * 3);
	    	path.push_back(c);
	  	}
		}

		path.push_back(coordinates()[curves * 3]); // Make sure the last point is included
	}

}
