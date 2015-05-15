#ifndef TRANSFORMATIONS__
#define TRANSFORMATIONS__

#include <array>
#include <iostream>
#include <ctgmath>
#include "cg/objects.h"


namespace CG{
	class Coordinate;

	/*
	 * Class represents a transformation matrix.
	 * Static methods build the appropriate matrix given the required parameters.
	 * Angles must be in radians.
	 */
	class Transformation{
		public:
			typedef std::array<std::array<double, 4>, 4> TransformationMatrix;
		private:
			TransformationMatrix _m;

		public:
			//default constructor builds an identity matrix;
			Transformation();
			Transformation(const double x[4][4]) {for(int i=0; i<4; i++) for(int j=0; j<4; j++)	_m[i][j]=x[i][j];}
			Transformation(TransformationMatrix&& m) : _m(m) {}
			Transformation(const TransformationMatrix& m) : _m(m) {}

			//getters
			const TransformationMatrix& m() const {return _m;}
			TransformationMatrix& m() {return _m;}

			//new transformations
			static Transformation newTranslation(double dx, double dy, double dz);
			static Transformation newScaling(double sx, double sy, double xz);
			static Transformation newScalingAroundObjCenter(double sx, double sy, double sz, const Coordinate& center);
			static Transformation newRx(double theta);
			static Transformation newRy(double theta);
			static Transformation newRz(double theta);
			static Transformation newRotation(double thetaX, double thetaY, double thetaZ, const Coordinate& p);

			//utils TODO: figure out where to put this
			static constexpr double pi() { return std::atan(1)*4; }
			static double toRadians(double degrees){ return (pi()/180) * degrees;  }

			//member operators
			Transformation& operator*=(const Transformation& rhs);
			Transformation transpose();
	};

	Transformation operator*(Transformation lhs, const Transformation& rhs);
	std::ostream& operator<<(std::ostream& os, const Transformation& rhs);
}

#endif
