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

	const std::string GObject::TypeNames[] = {"Object", "Point", "Line", "Polygon"};
}
