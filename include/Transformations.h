#ifndef TRANSFORMATIONS__
#define TRANSFORMATIONS__

#include <array>
#include <cmath>

namespace CG{
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
			static Transformation newRotation(float theta);

	};
}

#endif
