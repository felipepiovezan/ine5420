#ifndef TRANSFORMATIONS__
#define TRANSFORMATIONS__

#include <array>
#include <ctgmath>
#include "GObject.h"

namespace CG{
	class Coordinate;
	class GObject;
	class Transformation{
		public:
			typedef std::array<std::array<float, 3>, 3> TransformationMatrix;
		private:
			TransformationMatrix _m;

			Transformation(TransformationMatrix&& m) : _m(m) {}
		public:
			//getters
			const TransformationMatrix& m() const {return _m;}

			//new transformations
			static Transformation newTranslation(float dx, float dy);
			static Transformation newScaling(float sx, float sy);
			static Transformation newRotationAroundOrigin(float theta);
			static Transformation newRotationAroundPoint(float theta, const Coordinate& p);
			static Transformation newRotationAroundCenterOfMass(float theta, const GObject& obj);

			Transformation& operator*=(const Transformation& rhs);

	};
}

#endif
