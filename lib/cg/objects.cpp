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
		Coordinate r(0, 0, 0);
		int n = numPoints();

		for(auto &p : _coordinates){
			r.x += p.x;
			r.y += p.y;
			r.z += p.z;
		}

		r.x /= n;
		r.y /= n;
		r.z /= n;
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
	 * Recalculate the generated coordinates of the curve with specified step (0 to 1)
	 */
	void BezierCurve::regeneratePath(double step) {
		// The number of cubic curves to generate (4 points make 1 curve, 7 points make 2 curves etc)
		int curves = ((coordinates().size() - 4) / 3) + 1;
		const auto &coords = coordinates();
		path.clear();
		
		for (int i = 0; i < curves; i++) {
			/* calculate the polynomial coefficients */
			double   ax, bx, cx, dx;
			double   ay, by, cy, dy;
			cx = 3.0 * (coords[i*3 + 1].x - coords[i*3 + 0].x);
			bx = 3.0 * (coords[i*3 + 2].x - coords[i*3 + 1].x) - cx;
			ax = coords[i*3 + 3].x - coords[i*3 + 0].x - cx - bx;
			dx = coords[i*3 + 0].x;

			cy = 3.0 * (coords[i*3 + 1].y - coords[i*3 + 0].y);
			by = 3.0 * (coords[i*3 + 2].y - coords[i*3 + 1].y) - cy;
			ay = coords[i*3 + 3].y - coords[i*3 + 0].y - cy - by;
			dy = coords[i*3 + 0].y;
			/* calculate the curve point at parameter value t */
			for (double t = 0; t < 1; t += step) {
				double   tSquared, tCubed;
				double x,y;
				tSquared = t * t;
				tCubed = tSquared * t;

				x = (ax * tCubed) + (bx * tSquared) + (cx * t) + dx;
				y = (ay * tCubed) + (by * tSquared) + (cy * t) + dy;
				path.emplace_back(x,y);
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
