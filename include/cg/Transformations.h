#ifndef TRANSFORMATIONS__
#define TRANSFORMATIONS__

#include <array>
#include <iostream>
#include <ctgmath>
#include "cg/objects.h"

namespace CG{
	class Coordinate;
	class GObject;

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

			Transformation(TransformationMatrix&& m) : _m(m) {}
		public:
			//default constructor builds an identity matrix;
			Transformation();

			//getters
			const TransformationMatrix& m() const {return _m;}

			//new transformations
			static Transformation newTranslation(double dx, double dy, double dz);
			static Transformation newScaling(double sx, double sy, double xz);
			static Transformation newScalingAroundObjCenter(double sx, double sy, double sz, const GObject& obj);
			static Transformation newRx(double theta);
			static Transformation newRy(double theta);
			static Transformation newRz(double theta);
			static Transformation newRotation(double thetaY, double thetaZ, const Coordinate& p, double theta);

			//2d transformations. They assume a fixed z coordinate
			static Transformation newRotationAroundOrigin(double theta);
			static Transformation newRotationAroundPoint(double theta, const Coordinate& p);
			static Transformation newRotationAroundObjCenter(double theta, const GObject& obj);

			//utils TODO: figure out where to put this
			static constexpr double pi() { return std::atan(1)*4; }
			static double toRadians(double degrees){ return (pi()/180) * degrees;  }

			//member operators
			Transformation& operator*=(const Transformation& rhs);

	};

	std::ostream& operator<<(std::ostream& os, const Transformation& rhs);
}

#endif
