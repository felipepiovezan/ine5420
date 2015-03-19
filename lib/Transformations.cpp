#include "Transformations.h"


namespace CG{

	const double PI = atan(1) * 4;
	const double RAD = 180 / PI;

	Transformation Transformation::newTranslation(float dx, float dy){
		return Transformation
			({{ {1,  0,  0},
				{0,  1,  0},
				{dx, dy, 1}}});
	}

	Transformation Transformation::newScaling(float sx, float sy){
		return Transformation
			({{ {sx, 0 , 0},
				{0 , sy, 0},
				{0 , 0 , 1}}});
	}

	Transformation Transformation::newRotation(float theta){
		float radians = theta / RAD;
		return Transformation
			({{ {cosf(radians), -sinf	(radians), 0},
				{sinf(radians), cosf(radians) , 0},
				{0         , 0          , 1}}});
	}

	Transformation& Transformation::operator*=(const Transformation& rhs){
		auto m1 = this->_m;
		const auto &m2 = rhs.m();
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++){
				_m[i][j]=0;
				for(int k=0; k<3; k++)
					_m[i][j] += m1[i][k] * m2[k][j];
			}

		return *this;
	}

	Transformation operator*(Transformation lhs, const Transformation& rhs){
		lhs *= rhs;
		return lhs;
	}

}
