#ifndef TRANSFORMATIONS__
#define TRANSFORMATIONS__

#include <array>
#include <ctgmath>
#include "cg/GObject.h"

namespace CG{
	class Coordinate;
	class GObject;

	class Transformation{
		public:
			typedef std::array<std::array<double, 3>, 3> TransformationMatrix;
		private:
			TransformationMatrix _m;

			Transformation(TransformationMatrix&& m) : _m(m) {}
		public:
			//default constructor builds an identity matrix;
			Transformation();

			//getters
			const TransformationMatrix& m() const {return _m;}

			//new transformations
			static Transformation newTranslation(double dx, double dy);
			static Transformation newScaling(double sx, double sy);
			static Transformation newRotationAroundOrigin(double theta);
			static Transformation newRotationAroundPoint(double theta, const Coordinate& p);
			static Transformation newRotationAroundObjCenter(double theta, const GObject& obj);


			//utils TODO: figure out where to put this
			static constexpr double pi() { return std::atan(1)*4; }
			static double toRadians(double degrees){ return (pi()/180) * degrees;  }

			//member operators
			Transformation& operator*=(const Transformation& rhs);

	};
}

#endif
