#include "cg/objects.h"

namespace CG {
	Coordinate& Coordinate::operator*=(const Transformation& rhs){
		const auto &m = rhs.m();
		double x = this->x, y = this->y, z = this->z, w = this->w;
		this->x = x*m[0][0] + y*m[1][0] + z*m[2][0] + w*m[3][0];
		this->y = x*m[0][1] + y*m[1][1] + z*m[2][1] + w*m[3][1];
		this->z = x*m[0][2] + y*m[1][2] + z*m[2][2] + w*m[3][2];
		this->w = x*m[0][3] + y*m[1][3] + z*m[2][3] + w*m[3][3];
		return *this;
	}

	Coordinate operator*(Coordinate lhs, const Transformation& rhs){
		lhs *= rhs;
		return lhs;
	}

	Coordinate operator+(const Coordinate &c1, const Coordinate &c2) {
		return Coordinate(c1.x + c2.x, c1.y + c2.y, c1.z + c2.z);
	}

	Coordinate operator-(const Coordinate &c1, const Coordinate &c2) {
		return Coordinate(c1.x - c2.x, c1.y - c2.y, c1.z - c2.z);
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

	void GObject::applyPerspective(double dop) {
		for(auto &c : _coordinates) {
      c.x = dop * c.x / c.z;
      c.y = dop * c.y / c.z;
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
			double   az, bz, cz, dz;
			cx = 3.0 * (coords[i*3 + 1].x - coords[i*3 + 0].x);
			bx = 3.0 * (coords[i*3 + 2].x - coords[i*3 + 1].x) - cx;
			ax = coords[i*3 + 3].x - coords[i*3 + 0].x - cx - bx;
			dx = coords[i*3 + 0].x;

			cy = 3.0 * (coords[i*3 + 1].y - coords[i*3 + 0].y);
			by = 3.0 * (coords[i*3 + 2].y - coords[i*3 + 1].y) - cy;
			ay = coords[i*3 + 3].y - coords[i*3 + 0].y - cy - by;
			dy = coords[i*3 + 0].y;

			cz = 3.0 * (coords[i*3 + 1].z - coords[i*3 + 0].z);
			bz = 3.0 * (coords[i*3 + 2].z - coords[i*3 + 1].z) - cz;
			az = coords[i*3 + 3].z - coords[i*3 + 0].z - cz - bz;
			dz = coords[i*3 + 0].z;
			/* calculate the curve point at parameter value t */
			for (double t = 0; t < 1; t += step) {
				double tSquared, tCubed;
				double x, y, z;
				tSquared = t * t;
				tCubed = tSquared * t;

				x = (ax * tCubed) + (bx * tSquared) + (cx * t) + dx;
				y = (ay * tCubed) + (by * tSquared) + (cy * t) + dy;
				z = (az * tCubed) + (bz * tSquared) + (cz * t) + dz;
				path.emplace_back(x, y, z);
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

			double Az, Bz, Cz, Dz, deltaZ, delta2Z, delta3Z;
			coefficients(c1.z, c2.z, c3.z, c4.z, Az, Bz, Cz, Dz);
			differences(Az, Bz, Cz, Dz, step, step2, step3, deltaZ, delta2Z, delta3Z);

			Coordinate oldCoord(Dx, Dy, Dz);
			path.push_back(oldCoord);

			for (double t = 0.0; t <= 1; t += step) {
				Coordinate newCoord = oldCoord;
				newCoord.x += deltaX;
				newCoord.y += deltaY;
				newCoord.z += deltaZ;

				deltaX += delta2X;
				delta2X += delta3X;

				deltaY += delta2Y;
				delta2Y += delta3Y;

				deltaZ += delta2Z;
				delta2Z += delta3Z;

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


	constexpr double GSurface::bezier_matrix[4][4];
	constexpr double GSurface::spline_matrix[4][4];

	GSurface::GSurface(SurfaceType type, const Coordinates& coords) : GObject(coords),
			_geometry_matrix(type == SurfaceType::BEZIER? GSurface::bezier_matrix : GSurface::spline_matrix){
		regeneratePath(10, 10);
	}

	void GSurface::updateCoords(){
		for(int i = 0; i< 4; i++){
			_coords_x[0][i] = _coordinates[i].x;
			_coords_y[0][i] = _coordinates[i].y;
			_coords_z[0][i] = _coordinates[i].z;
		}
		for(int i = 0; i< 4; i++){
			_coords_x[1][i] = _coordinates[i+4].x;
			_coords_y[1][i] = _coordinates[i+4].y;
			_coords_z[1][i] = _coordinates[i+4].z;
		}
		for(int i = 0; i< 4; i++){
			_coords_x[2][i] = _coordinates[i+8].x;
			_coords_y[2][i] = _coordinates[i+8].y;
			_coords_z[2][i] = _coordinates[i+8].z;
		}
		for(int i = 0; i< 4; i++){
			_coords_x[3][i] = _coordinates[i+12].x;
			_coords_y[3][i] = _coordinates[i+12].y;
			_coords_z[3][i] = _coordinates[i+12].z;
		}
	}

	void GSurface::calculateCoefficients(){
		Transformation geometry(_geometry_matrix);
		Transformation geometryTransposed = geometry.transpose();

		Transformation coords_x(_coords_x);
		_cx = (geometry * coords_x * geometryTransposed).m();

		Transformation coords_y(_coords_y);
		_cy = (geometry * coords_y  * geometryTransposed).m();

		Transformation coords_z(_coords_z);
		_cz = (geometry * coords_z  * geometryTransposed).m();
	}

	void GSurface::createDeltaMatrices(double delta_s, double delta_t){
		  _es[0][0] = 0;
		  _es[0][1] = 0;
		  _es[0][2] = 0;
		  _es[0][3] = 1;

		  _es[1][0] = delta_s * delta_s * delta_s;
		  _es[1][1] = delta_s * delta_s;
		  _es[1][2] = delta_s;
		  _es[1][3] = 0;

		  _es[2][0] = 6 * delta_s * delta_s * delta_s;
		  _es[2][1] = 2 * delta_s * delta_s;
		  _es[2][2] = 0;
		  _es[2][3] = 0;

		  _es[3][0] = 6 * delta_s * delta_s * delta_s;
		  _es[3][1] = 0;
		  _es[3][2] = 0;
		  _es[3][3] = 0;

		  // Delta t
		  _et[0][0] = 0;
		  _et[1][0] = 0;
		  _et[2][0] = 0;
		  _et[3][0] = 1;

		  _et[0][1] = delta_t * delta_t * delta_t;
		  _et[1][1] = delta_t * delta_t;
		  _et[2][1] = delta_t;
		  _et[3][1] = 0;

		  _et[0][2] = 6 * delta_t * delta_t * delta_t;
		  _et[1][2] = 2 * delta_t * delta_t;
		  _et[2][2] = 0;
		  _et[3][2] = 0;

		  _et[0][3] = 6 * delta_t * delta_t * delta_t;
		  _et[1][3] = 0;
		  _et[2][3] = 0;
		  _et[3][3] = 0;
		  //transpose(_et); fiz isso mudando as atribuicoes acima...
	}

	void GSurface::createForwardDiffMatrices(){
	  Transformation es(_es), et(_et);
	  _DDx = (es * _cx * et).m();
	  _DDy = (es * _cy * et).m();
	  _DDz = (es * _cz * et).m();
	}

	void GSurface::makeCurve( int n,
	                      double x, double Dx, double D2x, double D3x,
	                      double y, double Dy, double D2y, double D3y,
	                      double z, double Dz, double D2z, double D3z){
	  int i = 0;
	  Coordinates coords;
	  coords.push_back(Coordinate(x,y,z));
	  for (i=1; i < n; i++) {
	    x = x + Dx;  Dx = Dx + D2x;  D2x = D2x + D3x;
	    y = y + Dy;  Dy = Dy + D2y;  D2y = D2y + D3y;
	    z = z + Dz;  Dz = Dz + D2z;  D2z = D2z + D3z;
			coords.push_back(Coordinate(x,y,z));
	  }
	  Curve c;
	  c.setPath(coords);
	  _curves.push_back(c);
	}

	void GSurface::UpdateForwardDiffMatrices(){
	  _DDx[0][0] =  _DDx[0][0]+_DDx[1][0]; _DDx[0][1] = _DDx[0][1]+_DDx[1][1]; _DDx[0][2] = _DDx[0][2]+_DDx[1][2]; _DDx[0][3] = _DDx[0][3]+_DDx[1][3];
	  _DDy[0][0] =  _DDy[0][0]+_DDy[1][0]; _DDy[0][1] = _DDy[0][1]+_DDy[1][1]; _DDy[0][2] = _DDy[0][2]+_DDy[1][2]; _DDy[0][3] = _DDy[0][3]+_DDy[1][3];
	  _DDz[0][0] =  _DDz[0][0]+_DDz[1][0]; _DDz[0][1] = _DDz[0][1]+_DDz[1][1]; _DDz[0][2] = _DDz[0][2]+_DDz[1][2]; _DDz[0][3] = _DDz[0][3]+_DDz[1][3];
	  _DDx[1][0] =  _DDx[1][0]+_DDx[2][0]; _DDx[1][1] = _DDx[1][1]+_DDx[2][1]; _DDx[1][2] = _DDx[1][2]+_DDx[2][2]; _DDx[1][3] = _DDx[1][3]+_DDx[2][3];
	  _DDy[1][0] =  _DDy[1][0]+_DDy[2][0]; _DDy[1][1] = _DDy[1][1]+_DDy[2][1]; _DDy[1][2] = _DDy[1][2]+_DDy[2][2]; _DDy[1][3] = _DDy[1][3]+_DDy[2][3];
	  _DDz[1][0] =  _DDz[1][0]+_DDz[2][0]; _DDz[1][1] = _DDz[1][1]+_DDz[2][1]; _DDz[1][2] = _DDz[1][2]+_DDz[2][2]; _DDz[1][3] = _DDz[1][3]+_DDz[2][3];
	  _DDx[2][0] =  _DDx[2][0]+_DDx[3][0]; _DDx[2][1] = _DDx[2][1]+_DDx[3][1]; _DDx[2][2] = _DDx[2][2]+_DDx[3][2]; _DDx[2][3] = _DDx[2][3]+_DDx[3][3];
	  _DDy[2][0] =  _DDy[2][0]+_DDy[3][0]; _DDy[2][1] = _DDy[2][1]+_DDy[3][1]; _DDy[2][2] = _DDy[2][2]+_DDy[3][2]; _DDy[2][3] = _DDy[2][3]+_DDy[3][3];
	  _DDz[2][0] =  _DDz[2][0]+_DDz[3][0]; _DDz[2][1] = _DDz[2][1]+_DDz[3][1]; _DDz[2][2] = _DDz[2][2]+_DDz[3][2]; _DDz[2][3] = _DDz[2][3]+_DDz[3][3];
	}

	void GSurface::regeneratePath(int ns, int nt){
		  updateCoords();
		  calculateCoefficients();
		  double delta_s = 1.0 / (ns - 1);
		  double delta_t = 1.0 / (nt - 1);
		  createDeltaMatrices(delta_s, delta_t);
		  createForwardDiffMatrices();
		  _curves.clear();
		  for (int i = 0; i < ns; i++) {
			  makeCurve(nt,
		                     _DDx[0][0], _DDx[0][1], _DDx[0][2], _DDx[0][3],
		                     _DDy[0][0], _DDy[0][1], _DDy[0][2], _DDy[0][3],
		                     _DDz[0][0], _DDz[0][1], _DDz[0][2], _DDz[0][3] );
		    UpdateForwardDiffMatrices();
		  }

		  createForwardDiffMatrices();
		  _DDx = Transformation(_DDx).transpose().m();
		  _DDy = Transformation(_DDy).transpose().m();
		  _DDz = Transformation(_DDz).transpose().m();
		  for (int i = 0; i < nt; i++) {
			  makeCurve(ns,
			  		                     _DDx[0][0], _DDx[0][1], _DDx[0][2], _DDx[0][3],
			  		                     _DDy[0][0], _DDy[0][1], _DDy[0][2], _DDy[0][3],
			  		                     _DDz[0][0], _DDz[0][1], _DDz[0][2], _DDz[0][3] );
		    UpdateForwardDiffMatrices();
		  }
	}

}
