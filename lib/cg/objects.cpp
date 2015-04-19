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

	SplineCurve::SplineCurve(const Coordinates& coords) {
		if (coords.size() < 4) {
			throw CGException("A spline curve must have at least 4 coordinates");
		}

		addCoordinate(coords);
		regeneratePath(0.1);
	}

	void SplineCurve::regeneratePath(double step) {
		path.clear();
		double step2 = step  * step;
		double step3 = step2 * step;

		auto coordinates = this->coordinates();
		int nCurves = coordinates.size() - 3; // number of curves defined on the spline

		for(int curve = 0; curve < nCurves; curve++) {
			auto c1 = coordinates[curve];
			auto c2 = coordinates[curve + 1];
			auto c3 = coordinates[curve + 2];
			auto c4 = coordinates[curve + 3];

			double Ax, Bx, Cx, Dx, deltaX, delta2X, delta3X;
			coefficients(c1.x, c2.x, c3.x, c4.x, Ax, Bx, Cx, Dx);
			differences(Ax, Bx, Cx, Dx, step, step2, step3, deltaX, delta2X, delta3X);

			double Ay, By, Cy, Dy, deltaY, delta2Y, delta3Y;
			coefficients(c1.y, c2.y, c3.y, c4.y, Ay, By, Cy, Dy);
			differences(Ay, By, Cy, Dy, step, step2, step3, deltaY, delta2Y, delta3Y);

			// double Az, Bz, Cz, Dz, deltaZ, delta2Z, delta3Z;
			// coefficients(c1.z, c2.z, c3.z, c4.z, Az, Bz, Cz, Dz);
			// differences(Az, Bz, Cz, Dz, step, step2, step3, deltaZ, delta2Z, delta3Z);

			Coordinate oldCoord(Dx, Dy);
			path.push_back(oldCoord);

			for (double t = 0.0; t <= 1; t += step) {
				Coordinate newCoord = oldCoord;
				newCoord.x += deltaX;
				newCoord.y += deltaY;
				//newCoord.z += deltaZ;
				deltaX += delta2X;
				delta2X += delta3X;

				deltaY += delta2Y;
				delta2Y += delta3Y;

				//deltaZ += delta2Z;
				//delta2Z += delta3Z;

				path.push_back(newCoord);
				oldCoord = newCoord;
			}
		}
	}

	void SplineCurve::coefficients(double c1, double c2, double c3, double c4,
																 double &A, double &B, double &C, double &D)
	{
		double d16 = 1.0 / 6.0;
		double d46 = 4.0 / 6.0;

		A = -d16 * c1 + 0.5 * c2 - 0.5 * c3 + d16 * c4;
		B =  0.5 * c1 -       c2 + 0.5 * c3;
		C = -0.5 * c1            + 0.5 * c3;
		D =  d16 * c1 + d46 * c2 + d16 * c3;
	}

	void SplineCurve::differences(double A, double B, double C, double D,
																double step, double step2, double step3,
																double &delta, double &delta2, double &delta3)
	{
		delta  = A * step3 + B * step2 + C * step;
		delta3 = 6 * A * step3;
		delta2 = delta3 + 2 * B * step2;
	}
}
